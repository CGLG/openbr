/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright 2012 The MITRE Corporation                                      *
 *                                                                           *
 * Licensed under the Apache License, Version 2.0 (the "License");           *
 * you may not use this file except in compliance with the License.          *
 * You may obtain a copy of the License at                                   *
 *                                                                           *
 *     http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                           *
 * Unless required by applicable law or agreed to in writing, software       *
 * distributed under the License is distributed on an "AS IS" BASIS,         *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 * See the License for the specific language governing permissions and       *
 * limitations under the License.                                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*!
 * \ingroup cli
 * \page cli_face_recognition Face Recognition
 * \ref cpp_face_recognition "C++ Equivalent"
 * \code
 * $ br -algorithm FaceRecognition \
 *      -compare ../data/MEDS/img/S354-01-t10_01.jpg ../data/MEDS/img/S354-02-t10_01.jpg \
 *      -compare ../data/MEDS/img/S354-01-t10_01.jpg ../data/MEDS/img/S386-04-t10_01.jpg
 * \endcode
 */

//! [face_recognition]
#include <openbr/openbr_plugin.h>
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

string type2str(int type);
/*
static void printTemplate(const br::Template &t)
{
    const QPoint firstEye = t.file.get<QPoint>("Affine_0");
    const QPoint secondEye = t.file.get<QPoint>("Affine_1");
    printf("%s eyes: (%d, %d) (%d, %d)\n", qPrintable(t.file.fileName()), firstEye.x(), firstEye.y(), secondEye.x(), secondEye.y());
}
*/

int main(int argc, char *argv[])
{
    br::Context::initialize(argc, argv);
    namedWindow("cam", WINDOW_NORMAL);
    cv::resizeWindow("cam", 200, 200);


    while (1) {
    // Retrieve classes for enrolling and comparing templates using the FaceRecognition algorithm
      QSharedPointer<br::Transform> transform = br::Transform::fromAlgorithm("FaceRecognition");
      QSharedPointer<br::Distance> distance = br::Distance::fromAlgorithm("FaceRecognition");

      // Initialize templates
      //br::Template queryA("0.webcam");
      string name("0.webcam");
      Mat mat = imread(name.c_str(), IMREAD_COLOR);
      br::Template target("/data/ATT/img/s1/1.pgm");


      // Enroll templates
      //mat >> *transform;

      // show webcam

      //Mat mat = queryA.m();
      if (!mat.data) {
        cout << "no data!\n";
      }
//      cout << "element size: " << mat.elemSize() << endl;
//      cout << "element size 1: " << mat.elemSize1() << endl;
      imshow("cam", mat);

      /*
      unsigned char* ptr = (unsigned char *) (mat.data);
      int i, j, r = 0, g = 0, b = 0;
      for (i = 0; i < mat.rows; i++) {
        for (j = 0; j < mat.cols; j++) {
          b = ptr[mat.step * j + i];
          g = ptr[mat.step * j + i + 1];
          r = ptr[mat.step * j + i + 2];
        }
        printf("BGR: %d, %d, %d\n", b, g, r);
      }
      */

      string ty =  type2str( mat.type() );
      printf("Matrix: %s %dx%d \n", ty.c_str(), mat.cols, mat.rows );


      if (waitKey(30) >= 0) {
          break;
      }

      target >> *transform;

      //printTemplate(queryA);
      //printTemplate(queryB);
      //printTemplate(target);

      // Compare templates
      //float comparisonA = distance->compare(target, queryA);

      // Scores range from 0 to 1 and represent match probability
      //printf("Genuine match score: %.3f\n", comparisonA);

    }
    br::Context::finalize();
    return 0;
}

string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}
//! [face_recognition]
