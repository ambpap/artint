# artint
A basic neural network made from scratch for studying human randomness

## about the project

It's a begginer project what was made to guess a number in a human generated "random" list of numbers between 1 and 10.
Turns out, a neural network is not the best tool for this kind of project. The accuracy of the network was 12% - basically the same as a random number generator.
Further experiments weren't made, it may work better with an iduvidual persons data.

The data was collected on paper with the following rules:
-the numbers must be as numbers as possible
-a number cannot appear twice in a row (this was used to valiadate the data (some of frinds tried to encode messages onto the paper))
-on a single paper there was 200 empty places for numbers, but it's not needed to fill all of them

Besides the faliures of the first modell, a second one was made for shape recognition to prove that the network itself works.
This modell recignizes four shapes: circle, triangle, X and smiley. the accuracy is around 85%

## usage
the code is not under any lincense and totally free to copy, but it's not very well written so I do not recommend using it. I recommend it for anyone who want's to create a simple neural network from scrach
here are my resources:

https://victorzhou.com/blog/intro-to-neural-networks/

http://neuralnetworksanddeeplearning.com/

https://github.com/mnielsen/neural-networks-and-deep-learning

https://www.youtube.com/watch?v=Ilg3gGewQ5U&list=PLZHQObOWTQDNU6R1_67000Dx_ZCJB-3pi&index=3

the training data is stored in training_data_row.txt for the random numbers and in project_b_training.txt for the shape recognizing network.
those helped me to better understand the basics of neural networks.
