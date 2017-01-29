# microSD card switcher
This board was created by [Joel Fernandez](http://www.linuxinternals.org/joel/) and a link to his blog post is given below
- [MicroSD card remote switch](http://www.linuxinternals.org/blog/2014/06/04/a-microsd-card-remote-switcher/)
- [Demo Video](https://youtu.be/StpIihVQ7oM)

## Features
- Connect one microSD card to 2 computers( or boards)
- Ensures that the sd card is connected to only one computer at a time
- Remotely control the switch over USB serial connection

## Parts list
- Circuit board - Make this yourself or use a vendor like [OSHPark](https://oshpark.com/), [Pcbway](http://www.pcbway.com/) etc
- [microSD card sniffer](https://www.sparkfun.com/products/9419) (2)
- [10k Resistors](https://www.sparkfun.com/products/11508) (2)
- [1k Resistors](https://www.sparkfun.com/products/13760) (2)
- [LEDs](https://www.sparkfun.com/products/12062) (2)
- [SN74CBT3257D - 4 bit FET Mux/DeMux](http://www.mouser.com/ProductDetail/Texas-Instruments/SN74CBT3257D) (2)
- [microSD slot](https://www.sparkfun.com/products/127) (1)
- [Male headers](https://www.sparkfun.com/products/116) (2)
- [FTDI Cable](https://www.sparkfun.com/products/9717)

## Building the switch program
### Using docker
If you have docker installed, just run the commands given below to get the built executable. The built executable works on 64 bit linux only.
    
    export MY_WORKSPACE=<you git workspace>
    chmod 777 $MY_WORKSPACE                                              # Need to do this so that root user in the container 
                                                                         # can write to the folder
    docker run -v $MY_WORKSPACE/sw:/workspace nbalagopal/microsd_switch  # 'switch' will be in your workspace.

### Directly on Linux
    # Install libftdi
    apt-get update -y
    apt-get install -y libftdi-dev libftdi1 libftdi1-dev libftdipp1-2v5 libftdipp1-dev
    
    # Install pkg-config
    apt-get install -y pkg-config
    
    # Verify libftdi installation
    pkg-config --cflags libftdi
    # Output:
    #  
    
    pkg-config --libs libftdi
    # Output: 
    #   -lftdi1
    
    # Build using gcc
    gcc $(pkg-config --cflags libftdi)  -o switch  switch.c  $(pkg-config --libs libftdi)
