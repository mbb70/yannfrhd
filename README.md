# yannfrhd
Yet Another Neural Network For Recognizing Handwritten Digits

## You've Heard This Story Before
A young lad reads some blog post about how neural networks are actually very simple and decided to give it a whack. Wow, just a
couple lines of python with numpy. But what about L1 and L2 regularization, different activation functions,
artificially expanding the dataset, momentum and all the other fun bells and whistles? Those tight lines of python can't fit
all that. So I did it up in C++. Keep in mind I don't know anything about C++ I didn't learn from StackOverflow, and I think
most of those questions were actually about C.

## Compiling
If you have c binding for BLAS installed it will be fine, just clean up the makefile a little bit. All the paramenters to hack
on are in the header.h file. With a little tuning it will hit 98%, with a lot of tuning it hits 99%.

## Features
- Standard single hidden layer with backprop with epochs and mini batches (H_N, EPOCHS, MINI_BATCH_SIZE)
- L1 / L2 Regularization (via LAMBDA)
- artificial dataset increase by doing small random shifts and rotations
- eta decay (ETA)
- sigmoid and rectified linear unit activation functions.
- softmax final layer
- momentum (BETA)
- threaded committee (different networks train separately on different threads, then pool results when testing)

## Things I might add
- parameterize more
- dropout
- early stopping
- more activation functions
- pretraining
- more hidden layers
- python wrapper for grid search of optimal parameters identification
