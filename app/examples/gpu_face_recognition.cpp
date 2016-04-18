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

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

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

    // Retrieve classes for enrolling and comparing templates using the FaceRecognition algorithm
    QSharedPointer<br::Transform> transform = br::Transform::fromAlgorithm("FaceRecognition");
    QSharedPointer<br::Distance> distance = br::Distance::fromAlgorithm("FaceRecognition");

    // Initialize templates
    br::Template queryA("0.webcam");
    br::Template target("/data/ATT/img/s1/1.pgm");

    while (1) {
      // Enroll templates
      queryA >> *transform;

      // show webcam
      Mat mat = queryA.m();
      imshow("cam", mat);

      target >> *transform;

      //printTemplate(queryA);
      //printTemplate(queryB);
      //printTemplate(target);

      // Compare templates
      float comparisonA = distance->compare(target, queryA);

      // Scores range from 0 to 1 and represent match probability
      printf("Genuine match score: %.3f\n", comparisonA);
      if (waitKey(30) >= 0) {
          break;
      }
    }
    br::Context::finalize();
    return 0;
}
//! [face_recognition]
