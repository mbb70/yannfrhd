# yannfrhd
Yet Another Neural Network For Recognizing Handwritten Digits

## You've Heard This Story Before
A young lad reads some article about how artificial neural networks are actually very simple and decided to give it a whack with the MNIST handwritten digits database. Wow, just a couple lines of python and numpy. But what about L1 and L2 regularization, different activation functions, artificially expanding the dataset, momentum, early stopping and all the other fun bells and whistles? Those tight lines of python can't fit all that. So I did it up in C++. Keep in mind I don't know anything about C++ I didn't learn from StackOverflow, and I think most of those questions were actually about C.

## Compiling
A sane UNIX environment with C binding for BLAS installed should compile it just fine. My environment is not a sane one though, so you'll need to fix up the makefile a little bit. All the tunable paramenters to hack on are in the header.h file. The current defaults will hit 97% in 30 seconds, 98% in 2 minutes and 99% in about 40 minutes on my computer.

## Features
- Standard single hidden layer with backprop with epochs and mini batches (H_N, EPOCHS, MINI_BATCH_SIZE)
- L1 / L2 Regularization (LAMBDA)
- artificial dataset increase by doing small random shifts and rotations
- eta decay (ETA)
- sigmoid and rectified linear unit activation functions.
- softmax final layer
- momentum (BETA)
- threaded committee (different networks train separately on different threads, then pool results when testing)

## Things I might add
- better parameterization
- utilize GPU through OpenCL
- dropout
- early stopping
- more activation functions
- pretraining
- more hidden layers
- python wrapper for grid search of optimal parameters
