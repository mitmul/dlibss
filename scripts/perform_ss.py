#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
sys.path.append('lib/build')
import os
import dlibss
import numpy as np
import cv2 as cv

if __name__ == '__main__':
    img = cv.imread(sys.argv[1])
    canvas = np.zeros((img.shape[0], img.shape[1]))

    rects = dlibss.selective_search(
        img, 50, 200, 3, 20, 50)

    if not os.path.exists('tmp'):
        os.mkdir('tmp')

    for i, rect in enumerate(rects):
        l, t, r, b = rect
        canvas[t:b, l:r] += 1
        cv.imwrite('tmp/%d.jpg' % i, img[t:b, l:r])
    canvas = canvas / np.max(canvas) * 255
    cv.imwrite('%s_ss.jpg' % sys.argv[1], canvas)
