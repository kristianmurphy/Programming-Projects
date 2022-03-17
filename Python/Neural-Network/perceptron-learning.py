# Perceptron learning
import numpy as np
import matplotlib.pyplot as plt

# creates a class NeuralNetwork(): that creates a single neuron, trains it, and tests it

# i. Class to create a neural network with single neuron
class NeuralNetwork(object):
    def __init__(self):
      self.weight_matrix=2*np.random.random((3, 1)) - 1    # 3x1 Weight matrix
                                                #random weights between -1 and 1
      self.l_rate=1 # Learning rate set to 1
    
    # ii. hard_limiter as activation function
    def hard_limiter(self, x):
      outs=np.zeros(x.shape)
      outs[x>0]=1
      return outs

    # iii. forward propagation
    def forward_propagation(self, inputs):
      outs=np.dot(inputs, self.weight_matrix)
      return self.hard_limiter(outs)    

    # iv. training the neural network.
    def train(self, inputs, labels, num_train_iterations=10):
      #Number of iterations we want to perform for this set of input.
      for iteration in range(num_train_iterations):
        #updating the perceptron base on the misclassified examples
        for i in range(inputs.shape[0]):
          pred_i = self.pred(inputs[i,:])
          if pred_i!=labels[i]:
            output = self.forward_propagation(inputs[i,:])
            #Calculate the error in the output.
            error = labels[i] - output
            adjustment = self.l_rate*error*inputs[i]
            #Adjust the weight matrix
            self.weight_matrix[:,0] += adjustment
            # plot the separating line based on the weights
            print('Iteration #'+str(iteration))
            plot_fun_thr(inputs[:,1:3], labels, self.weight_matrix[:,0], classes)
      for j in range(inputs.shape[0]):
        if (inputs[j,1])*self.weight_matrix[1]+(inputs[j,2])*self.weight_matrix[2]+self.weight_matrix[0] <= 0:
          predicted = 0
        else:
          predicted = 1
        print('input: ' + str(inputs[j]) + '\tDesired label: ' + str(labels[j]) + '\tPredicted label: ' + str(predicted))

    #v. predicting the classes of new data points
    def pred(self, inputs):
      preds=self.forward_propagation(inputs)
      return preds

# Plotting function
def plot_fun_thr(features, labels,thre_parms,classes):
      #plotting the datapoints
      plt.plot(features[labels[:]==classes[0],0], features[labels[:]==classes[0],1], 'rs',
             features[labels[:]==classes[1],0], features[labels[:]==classes[1],1],'g^')
      plt.axis([-4,4,-4,4])
      #plotting the separating line
      x1=np.linspace(-4,4,50)
      x2=-(thre_parms[1]*x1+thre_parms[0])/thre_parms[2] #a X1 + b X2 + c=0 --> x2 = -(a X1 + c)/b
      plt.plot(x1, x2, '-r')
      plt.xlabel('x: feature 1')
      plt.ylabel('y: feature 2')
      plt.legend(['Class'+str(classes[0]), 'Class'+str(classes[1])])
      #plt.pause(0.5)
      plt.show()

# uses the perceptron learning rule to train a single neuron on the data points

# i.
ifeatures = np.array([[1,1], [1,0], [0,1], [-1,-1], [-1,0], [-1,1]]) # Initialize the points given in the data table in part e. 
print(ifeatures)
ilabels=np.array([1,1,0,0,0,0]) # Set desired labels for each element/point
print(ilabels)
classes=[0,1]

# ii.
bias = np.ones((ifeatures.shape[0],1)) # Use bias = 1
print(bias)
print(bias.shape)
ifeatures = np.append(bias,ifeatures, axis=1) ## append features to bias so that bias comes before the data points
print(ifeatures)
print(ifeatures.shape)

# plotted data points and classifier line

# iii.
neural_network = NeuralNetwork()
print('Random weights at the start of training')
print(neural_network.weight_matrix)
neural_network.train(ifeatures, ilabels,100)
# creation of neural network and then print data
print('New weights after training')
print(neural_network.weight_matrix)

# uses the trained perceptron and classify the test data samples given in the table below 
by calling the pred() function

newinputs = np.array([[2,0],[2,1],[0,0],[-2,0]]) #based on new table in part c, make new data points
newlabels = np.array([1,0,1,0])#and make new desired labels to match
print(newinputs)
bias = np.ones((newinputs.shape[0],1))
print(bias)
newinputs = np.append(bias,newinputs, axis=1)
print(newinputs)
for i in range(newinputs.shape[0]): ## use pred() in the print line below to predict the label for the table in part c, based on the trained perceptron
  print('Input: ' + str(newinputs[i]) +'\tDesired label: ' + str(newlabels[i]) + '\tPredicted label:'+str(neural_network.pred(newinputs[i])))
#50% accuracy