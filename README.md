Converts the infix expression to a postfix expression and calculate

# Reading Function
This program read function from "input.txt" file which in the same folder with executable form of this.

# Input and Output Type
Variables must be one character, every part of function must be divided by whitespace

a = 2 ;

b = 3 ;

c = a * ( b + 4 ) ;

b = c + b * 2 ;

d = a * ( b - c ) / 2 ;


# The Final State of Variables

a<-2    b<-20    c<-14    d<-6


#For example one step

Operation :

d = a * ( b - c ) / 2 ;


Infix translated to postfix...

Postfix: a                                                 Stack: empty

Postfix: a                                                 Stack: *

Postfix: a                                                 Stack: * (

Postfix: a b                                               Stack: * (
Postfix: a b                                               Stack: * ( -

Postfix: a b c                                             Stack: * ( -

Postfix: a b c -                                           Stack: *

Postfix: a b c - *                                         Stack: /

Postfix: a b c - * 2                                       Stack: /

Postfix: a b c - * 2 /                                     Stack: empty



Calculating for postfix: a b c - * 2 /  variables: a<-2  b<-20  c<-14

Stack: 2

Stack: 2 20

Stack: 2 20 14

Stack: 2 6

Stack: 12

Stack: 12 2

Stack: 6



d <- 6