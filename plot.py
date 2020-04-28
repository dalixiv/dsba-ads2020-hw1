#!/usr/bin/env python
# coding: utf-8

# In[6]:


import matplotlib.pyplot as plt
import csv
import numpy as np

y1 = []
y2 = []
y3 = []
x = []

with open('results.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(int(row[0]))
        y1.append(float(row[1]))
        y2.append(float(row[2]))
        y3.append(float(row[3]))

x = np.array(x)

plt.plot(x, y1, label='SchoolGrade') 
plt.plot(x, y2, label='Karatsuba')
plt.plot(x, y3, label='DaC') 
plt.grid()     
plt.xlabel('Number length')
plt.ylabel('Time in mls')
plt.legend()
plt.show()


# In[ ]:





# In[ ]:




