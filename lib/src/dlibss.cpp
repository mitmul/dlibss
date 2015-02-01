#include <vector>
#include <string>
#include <opencv.hpp>
#include <dlib/opencv.h>
#include <dlib/image_transforms.h>
#include <boost/python.hpp>
#include <boost/numpy.hpp>

namespace py = boost::python;
namespace np = boost::numpy;

cv::Mat convert_to_cvmat(const np::ndarray &img) {
  size_t rows = img.shape(0), cols = img.shape(1), channels = img.shape(2);
  unsigned char *data = reinterpret_cast<unsigned char *>(img.get_data());
  cv::Mat img_mat(rows, cols, CV_8UC(channels));
  memcpy(data, img_mat.data, rows * cols * channels);

  return img_mat;
}

np::ndarray selective_search(
  const np::ndarray &img,
  const int &start,
  const int &end,
  const int &num,
  const int &min_size,
  const int &max_iter) {

  cv::Mat img_mat = convert_to_cvmat(img);
  dlib::cv_image<dlib::bgr_pixel> cimg(img_mat);
  std::vector<dlib::rectangle> rects;

  dlib::find_candidate_object_locations(
    cimg,
    rects,
    dlib::linspace(start, end, num),
    min_size,
    max_iter);

  py::tuple shape = py::make_tuple(rects.size(), 4);
  np::dtype dtype = np::dtype::get_builtin<int>();
  np::ndarray result = np::zeros(shape, dtype);
  int *result_data = reinterpret_cast<int *>(result.get_data());

  for (int i = 0; i < rects.size(); ++i) {
    result_data[i * 4 + 0] = rects[i].left();
    result_data[i * 4 + 1] = rects[i].top();
    result_data[i * 4 + 2] = rects[i].right();
    result_data[i * 4 + 3] = rects[i].bottom();
  }

  return result;
}

BOOST_PYTHON_MODULE(dlibss) {
  np::initialize();

  py::def("selective_search", selective_search);
}