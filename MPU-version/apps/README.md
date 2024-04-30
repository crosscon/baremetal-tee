# Examples
## blinky_l475
Blinks LED, the `main()` function can be changed to toggle different LEDs: green led or network led (yellow and blue). Its makefile can be used as a template for application fortification.

## flash_l465
Application that attempts to write flash memory, when fortified the application will fail due to ACP violation.
Its makefile is configured to produce both the non-fortified and fortified version in order to compare their behaviour.

## benchmark_prime
Application that computes whether a series of numbers are prime or not, used as a benchmark.
Its makefile is preconfiured to produce fortified and non-fortified version of the benchmark.

## benchmark_factorization
Application that performs the factorization of a series of large prime numbers, used as a benchmark.
Its makefile is preconfiured to produce fortified and non-fortified version of the benchmark.

## buffer_overflow_l475
Application showing off a buffer overflow vulnerability resulting in malicious code execution.
Its makefile is preconfiured to produce fortified and non-fortified version of the benchmark.
The main function will toggle the green led on and off a coupe of time before triggering the vulnerable function.
When the non-fortified application is executing, the buffer overflow vulnerability is exploited resulting the the execution of malicious code which will call the function `toggle_network_led()` that toggles the yellow and blue leds.
On the other hand, it can be observed how the fortified version never calls such function. In fact the green led is toggled at the beginning but the yellow and blue led are never toggled.

## http_vulnerable_l475
Application showing off an HTTP server vulnerable to a buffer overread attack that can bea used to leak sensitive information.
Its makefile is preconfiured to produce fortified and non-fortified version of the benchmark.
The `main.c` file contains the configuration information (Wi-Fi SSID and password) that needs to be customized before the application is launched.
Once the web server is up and running, the elevation of different european capitals can be requested as well as toggling the onboard led on and off.
The "Advanced Information" section shows which address is being accessed to retrieve the requested elevation.
The vulnerability is due to the fact that the index used to access the array containing the capitals elevation is not checked for boundries, which allow the malicious user to access any memory location. Selecting an index of `100657433` will access memory address `0x20000040` (the address accessed differs slightly between fortified and non-fortified version to due the initial location of the array).
When the non-fortified application is executing, the buffer overread vulnerability can be exploited to read any memory location.
On the other hand, it can be observed how the fortified version detects the unauthorized access (e.g. when attempting to use index `100657433`) resulting in a hand of the web server. Additionally the error is reported after reboot.