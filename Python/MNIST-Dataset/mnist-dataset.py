# MNIST dataset

from keras.datasets import mnist  # Images for data sets
import matplotlib.pyplot as plt  # Plotting functions for images
import numpy as np              # NumPy for mathematical functions
import random                  # Randomization to generate numbers with

(x_train1, y_train1), (x_test, y_test) = mnist.load_data() # Name training set "..train1" because it will be renamed to "..train" later on
# The x arrays will be images while the y arrays will be the matching labels
# Print training set
print('Number of images in training set: ' + str(x_train1.shape[0])) # Using shape [0] element to get the size of the array of images
print('Image width x height: ' + str(x_train1.shape[1]) + ' x ' + str(x_train1.shape[2])) # Using the [1] and [2] elements of shape to get dimensions of images
# Print testing set
print('Number of images in test set: ' + str(x_test.shape[0])) # Using shape [0] element to get the size of the array of images
print('Image width x height: ' + str(x_test.shape[1]) + ' x ' + str(x_test.shape[2])) # Using the [1] and [2] elements of shape to get dimensions of images


def splot(images, labels): # Function definition - takes input array of images, and array of labels to match
  fig, axs = plt.subplots(2,5) # Initialize subplot with 2 rows and 5 columns
  image_num = int(0) # Initialize counter to keep track of which digit is currently being chosen and printed
  for a in range(2): # For loop to go through the two rows one at a time
    for b in range(5): # For loop to make 5 entries for each row, making 5 columns
      axs[a,b].plot() # Start the cell for plotting
      images_d=images[labels==image_num,:,:] # Create the array of images that match the current number starting from 0 and going to 9 (limited by the for loops 2x5=10 digits)
      randomindex = random.randint(-1, (images_d.shape[0])) # Create a random index chosen between the bounds of -1 and the size of image digit array (not including the limits)
      
      images_i=images_d[randomindex,:,:] # new images array using the random index to choose from the array of images matching current digit
      axs[a,b].imshow(images_i,cmap='gray') # set up image for plotting grayscale array 
      axs[a,b].set_title('Label: ' + str(image_num)) # label each plot with the correct image number digit
      image_num += 1 # increment the image number by 1 with each cell that is created to keep track of current digit
  plt.show() # at the end of plotting, show the current plot as to keep the printed text in order
  return # function ends, return back to main program



num_train_img=x_train1.shape[0] # Find the number of trained images in the trained set shape [0] element
train_ind=np.arange(0,num_train_img) # Create the train index list from 0 to the number of trained images recorded

train_ind_s=np.random.permutation(train_ind) # Randomize the permutations in the train index list

x_train=x_train1[train_ind_s,:,:] # Create the new x train list with the proper name, taking from x train 1 in new order
y_train=y_train1[train_ind_s] # Create the new y train list with the proper name, taking from y train 1 in new order

x_valid=x_train1[0:int(0.2*num_train_img),:,:] # Create the valid image set with 20% of the trained set
y_valid=y_train1[0:int(0.2*num_train_img)] # Create the valid label set with 20% of the trained set

x_train=x_train1[int(0.2*num_train_img):,:,:] # Remake the trained set with the upper 80% of its old self
y_train=y_train1[int(0.2*num_train_img):] # Remake the trained set with the upper 80% of its old self

print("Number of images in training set: " + str(x_train.shape[0])) # Print the total number of images in the trained set

print("Number of images in validation set: " + str(x_valid.shape[0])) # Print the total number of images in the validation set


titlesarray = ("Training set", "Testing set", "Validation set") # Create array of titles of the sets

imagesarray = (x_train, x_test, x_valid) # Create array of image sets
labelsarray = (y_train, y_test, y_valid) # Create array of label sets

for i in range(len(titlesarray)): # Loop through the sets, making sure that each array has matching elements with its correct set
  print("\n" + titlesarray[i]) # Print the title of the set
  splot(imagesarray[i],labelsarray[i]) # followed by its subplot