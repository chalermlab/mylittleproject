#!/usr/bin/perl -w
#
# Simple Tk script to create a button that prints "Hello, world". Click on
# the button to terminate the program.
#
# The first line below imports the Tk objects into the application, the
# second line creates the main window, the third through fifth lines create
# the button and define the code to execute when the button is pressed, the
# sixth line asks the packer to shrink-wrap the application's main window
# around the button, and the seventh line starts the event loop.
 
use Tk;
$MW = MainWindow->new;
$hello = $MW->Button(
    -text    => 'Stoppa agget for boveln!',
    -command => sub {print STDOUT "Stoppa agget för böveln!\n"; exit;} );
$hello->pack;
MainLoop;
