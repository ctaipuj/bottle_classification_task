# Bottle Classification Task (Deprecated)
Here you can find a computer vision algorithm designed to classify three polymers: Colored HDPE, HDPE/PS and Green colored PET. Using *OpenCV* libraries and a kinect sensor. 

This code is only used for evaluation purposes. Please refer to [https://github.com/ctaipuj/lenny_vision](lenny_vision) for further information.

+++++THIS CODE IS UNSTABLE+++++

## Contents:
This section has the following .cpp files and three .h files in the include directory:
### include Directory:
1. **detection.h** Declares the polycolor class used for the detection of the bottles in the scene and classify them in the three categories
2. **perception.h** Declares the space class used to estimate the 3D pose of the bottle
3. **test.h** Declares the test class (Deprecated)
### src Directory:
1. **main.cpp** Is the main
2. **polycolor.cpp** Describes the polycolor class
3. **space.cpp** Describes the space class
4. **suma.cpp** Merges three single-channel images into a three-channels one
5. **test.cpp** Describes the test class (Deprecated). Useless

*Creaded by Nicolas May 2018*
