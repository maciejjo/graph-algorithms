# -*- coding: utf-8 -*- at

import matplotlib.pyplot as plt
import csv
from matplotlib.backends.backend_pdf import PdfPages
pp = PdfPages('sortings.pdf')

with open('pomiary.csv') as csvfile:
	reader = csv.reader(csvfile)
	adj_matrix_count = []
	adj_matrix_times = []
	adj_list_count = []
	adj_list_times = []
	edge_list_count = []
	edge_list_times = []
	for row in reader:
		if(row[0] == "Adjacency matrix"):
			adj_matrix_count.append(int(row[1]))
			adj_matrix_times.append(float(row[2]))
		if(row[0] == "Adjacency list"):
			adj_list_count.append(int(row[1]))
			adj_list_times.append(float(row[2]))
		if(row[0] == "Edge list"):
			edge_list_count.append(int(row[1]))
			edge_list_times.append(float(row[2]))
	
	plt.plot(adj_matrix_count, adj_matrix_times, marker='o', color='red', linewidth=2.5, linestyle='-', label="Adjacency matrix")
	plt.plot(adj_list_count, adj_list_times, marker='o', color='green', linewidth=2.5, linestyle='-', label="Adjacency list")
	plt.plot(edge_list_count, edge_list_times, marker='o', color='blue', linewidth=2.5, linestyle='-', label="Edge list")
	plt.suptitle("Topological sorting", fontsize=20)
	plt.legend(loc='upper right')
	plt.ylabel('Time in seconds')
	plt.xlabel('Number of elements')
	plt.grid(True)
	pp.savefig()
	plt.clf()

pp.close()
			
