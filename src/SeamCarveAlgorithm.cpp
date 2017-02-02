/*
 * SeamCarveAlgorithm.cpp
 * Defines the seam carving algorithm.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 */

#include "SeamCarveApp.hpp"

#define min(x, y)           ((x) < (y) ? (x) : (y))


/**
 * @brief Peforms the seam carving algorithm.
 *
 * @param smap 2-d saliency map with width `w` and height `h`; can be
 * indexed by `smap[i][j]`
 *
 * @param w Width of the saliency map
 *
 * @param h Height of the saliency map
 *
 * @return An array of the x-coordinates of the seam, starting from the top of
 * the image.
 */
unsigned int *DoSeamCarve(unsigned int **smap, int w, int h)
{
    /* TODO: Write this function! */
   int **arr = new int*[w];
   for (int i = 0;i < w;i++) {
	   arr[i] = new int[h];
   }
   
   for (int i = 0;i < w;i++) {
	   arr[i][0] = smap[i][0];
   }
   
   int minimum;
   for (int j = 1;j < h;j++) {
		for (int i = 0;i < w;i++) {
		   minimum = arr[i][j - 1];
		   if (i != 0) {
			   minimum = min(minimum, arr[i - 1][j - 1]);
		   }
		   if (i != w - 1) {
			   minimum = min(minimum, arr[i + 1][j - 1]);
		   }
		   arr[i][j] = minimum + smap[i][j];
	   }
   }
	   
    unsigned int *seam = new unsigned int[h];
    int minindex, newindex;
    
    minimum = arr[0][h - 1];
    for (int i = 1;i < w;i++) {
		if (arr[i][h - 1] < minimum) {
			minimum = arr[i][h - 1];
			minindex = i;
		}
	}
	
	seam[h - 1] = minindex;

    for (int i = h - 2; i >= 0; i--) {
		minindex = seam[i + 1];
		newindex = seam[i + 1];
		minimum = arr[minindex][i];
		if (minindex > 0) {
			if (arr[minindex - 1][i] < minimum) {
				minimum = arr[minindex - 1][i];
				newindex = minindex - 1;
			}
		}
		if (minindex  < w - 1) {
			if (arr[minindex + 1][i] < minimum) {
				minimum = arr[minindex + 1][i];
				newindex = minindex + 1;
			}
		}
        seam[i] = newindex;
    }
    
    for (int i = 0; i < w;i++) {
		delete[] arr[i];
	}
	delete[] arr;

    return seam;
}

