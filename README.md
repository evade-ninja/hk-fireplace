# hk-fireplace
HomeSpan based Fireplace controller. Pretends to be a light since there isn't a fireplace in HomeKit. Provisions for a relay and a switch. The fireplace this is designed for has a pair of terminals that when shorted cause the fireplace to turn on, when open it turns off. 
This sketch is designed to use a momentary switch to trigger the relay to turn on, and to trigger turning off.

The bulk of this sketch comes from the HomeSpan examples, primarily #15. The minimal need for modification is a testament to the quality of the HomeSpan examples.
