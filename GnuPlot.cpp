#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GnuPlot.h"

using namespace std;
namespace project{
    void GnuPlot::plotResults() const
    {
        vector<int> xData;
        int N = (dataSize)/2;
        for (int i = -N+1; i <= N; i++) 
        {
            xData.push_back(i);
        }
        
        FILE *gnuplotPipe,*tempDataFile;
        const char *tempDataFileName1 = "Beat";
        const char *tempDataFileName2 = "Meet";
        const char *tempDataFileName3 = "Miss";
        
        const char *title = "Avg CAAR for 3 groups";
        const char *xlabel = "Announcement Date";
        const char *ylabel = "Avg CAAR(%)";
        
        gnuplotPipe = popen("gnuplot -persist", "w");
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "set title '%s'\n", title);
        
        fprintf(gnuplotPipe, "set arrow from 0,graph(0,0) to 0,graph(1,1) nohead lc rgb 'red'\n");
        fprintf(gnuplotPipe, "set xlabel '%s'\n set ylabel '%s'\n", xlabel, ylabel);
        
        if (gnuplotPipe) 
        {
            fprintf(gnuplotPipe,"plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines\n", tempDataFileName1, tempDataFileName2, tempDataFileName3);
            fflush(gnuplotPipe);
            
            // Figure 1
            tempDataFile = fopen(tempDataFileName1,"w");
            for (int i=0; i < dataSize; i++) {
                if (isnan(yData1[i])){
                    fprintf(tempDataFile,"%d %lf\n",xData[i],0.0);
                }
                else{
                    fprintf(tempDataFile,"%d %lf\n",xData[i],yData1[i]);
                }
            }
            fclose(tempDataFile);
            
            // Figure 2
            tempDataFile = fopen(tempDataFileName2,"w");
            for (int i=0; i < dataSize; i++) {
                if (isnan(yData2[i])){
                    fprintf(tempDataFile,"%d %lf\n",xData[i],0.0);
                }
                else{
                    fprintf(tempDataFile,"%d %lf\n",xData[i],yData2[i]);
                }
            }
            fclose(tempDataFile);
            
            // Figure 3
            tempDataFile = fopen(tempDataFileName3,"w");
            for (int i=0; i < dataSize; i++) {
                if (isnan(yData3[i])){
                    fprintf(tempDataFile,"%d %lf\n",xData[i],0.0);
                }
                else{
                    fprintf(tempDataFile,"%d %lf\n",xData[i],yData3[i]);
                }
            }
            fclose(tempDataFile);
            
            // Exit
            printf("Plotting, press enter to continue...");
            getchar();
            
            // Clear
            // remove(tempDataFileName1);
            // remove(tempDataFileName2);
            // remove(tempDataFileName3);
            
            fprintf(gnuplotPipe,"Plot Exited \n");
        } 
        else 
        {        
            printf("gnuplot not found...");    
        }
    }
}