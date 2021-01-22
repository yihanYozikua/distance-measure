# Here to record the steps of the analysis

## How to find that the diatance between screen and user is illegal
1. Init the distance
  F = (P * D) / W
  focal_length = ( pixel_of_obj * distance_to_obj ) / horizontol_width_of_obj

  F: focal length (macOS's = 50mm)
  P: Pixel
  D: Distance
  W: Width

  D' = ( F * W ) / P

2. Record the P (Record the size of the eyes)
3. analyze the P' (Analyze the size fo the eyes)
4. If the P' __(try & error)__ times bigger than the P, then send the notification


## main.cpp Logic
1. load the .xml of faces&eyes classifier
2. cvtColor(): convert the image into grayscale, lower the amount of calculation
3. equalizeHist(): histogram to stronger the contrast
4. use the XML inside the classifier to detect faces and eyes
5. circle the eyes