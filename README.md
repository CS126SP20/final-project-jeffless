# Final Project

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

## Introduction
ToBoard is a collaborative whiteboard which allows students to work on problems together. Students can simultaneously 
draw on an empty whiteboard.

## Dependencies
 * [Cinder](https://libcinder.org/download)
 * [mongocxx driver](http://mongocxx.org/mongocxx-v3/installation)


## Build Instructions
Instructions will assume that you are working within the [CLion IDE](https://www.jetbrains.com/clion/)
1. Set up Cinder (instructions modified from [UIUC CS 126 Spring 2020](https://courses.grainger.illinois.edu/cs126/sp2020/assignments/snake/))
    * Download [Cinder](https://libcinder.org/download) (v0.9.2) for your platform. Extract the downloaded item into a folder. We’ll call this folder `~/Cinder` throughout the instructions
    * Open the `~/Cinder` folder in CLion and click the green build button. This will build `libcinder`. You only need to do this once per machine. This build might take a while.
    * Create a directory, say `my-projects` in `~/Cinder`. Clone the `final-project` project into this folder. You can checkout your repository here.
2. Install the [mongocxx driver](http://mongocxx.org/mongocxx-v3/installation) (r3.5.0)

## Run Instructions
 * Follow [instructions](https://docs.mongodb.com/guides/server/install) to install MongoDB on your platform
 * [Start a MongoDB instance](https://docs.mongodb.com/guides/server/install/#run-mongodb) on localhost:27017
    * If for any reason you have to use another port, modify the `kDatabaseUri` variable in `database_manager.h`
 * Open the `final-project` project in CLion, set the target to `cinder-myapp` and click the run button.


**Author**: Jeffrey Lin - [`jl108@illinois.edu`](mailto:jl108@illinois.edu)
