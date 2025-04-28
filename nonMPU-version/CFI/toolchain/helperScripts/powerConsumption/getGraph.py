#!/bin/python3

#    Author: Michele Grisafi
#    Email: michele.grisafi@unitn.it
#    License: MIT 
import matplotlib.pyplot as plt
import pandas as pd
import os
import csv

#Directory with the results
directory = "results"

#Cycle through the files in the directory
for entry in sorted(os.scandir(directory),key=lambda e: e.name):
    #If it is a file
    if (entry.path.endswith(".csv") and entry.is_file()):
        print("Plotting {}\n".format(entry.name))

        #Read data and plot them
        df = pd.read_csv(entry.path)

        #Get the name of the file, which is the last segment of the path
        name=entry.name.split(".")[1]
        if name == "FlaMod":
            name="Flashadow"
            linestyle='solid'
        elif name == "PisMod":
            name="Pistis"
            linestyle='dashed'
        elif name == "PisNat":
            name="Pistis non instrumented"
            linestyle='dotted'
        elif name == "FlaNat":
            name="Flashadow non instrumented"
            linestyle='dashdot'

        
        plt.plot(df.Rate,df.Years,linewidth=2,label=name,ls=linestyle)

        #Only create one file for each couple of measurements
        if(entry.path.endswith(".PisNat.csv")):
            plt.xlabel("Execution interval (s)")
            plt.ylabel("Duration (Years)")

            #Define the various X ticks
            my_xticks = ['1s','1m','5m','30m','1h','6h','12h']

           

            #X-axis ticks in seconds
            x_ticks = [1,60,300,1800,3600,21600,43200]
            print(plt.xticks(x_ticks, my_xticks))
            
            #Set maximum x-axis length
            plt.axis(xmin=1,xmax=1400)

            #Define the scale to log
            plt.xscale('log')
            plt.legend()
            #Save the graphs
            plt.savefig("results/figures/"+entry.name[0:entry.name.index(".PisNat.csv")]+".png")
            print("Saving fig {}\n".format(entry.name[0:entry.name.index(".PisNat.csv")]))
            plt.clf()








