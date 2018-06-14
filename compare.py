#! /usr/bin/env python3

import sys
import json

def compare_statistics(data1, data2):
  statistics1 = data1["statistics"]
  statistics2 = data2["statistics"]

  print ("%-25s| %11s | %11s | %-6s" % (metric, "value1", "value2", "speedup"))
  print (25*"-" + "| " + 12*"-" + "| " + 12*"-" + "|" + 8*"-")
  for (d1k, d1v), (d2k, d2v) in zip(statistics1.items(), \
                                    statistics2.items()):
    value1 = d1v[metric]["mean"]
    value2 = d2v[metric]["mean"]
    diff = value1/value2
    print("{:25s}| {:>11.4f} | {:>11.4f} | {:>7.4f}".format(d1k, value1, value2, diff))

def compare_iteration0(data1, data2):
  iteration1 = data1["iteration-0"]
  iteration2 = data2["iteration-0"]

  print ("%-25s| %11s | %11s | %-6s" % (metric, "value1", "value2", "speedup"))
  print (25*"-" + "| " + 12*"-" + "| " + 12*"-" + "|" + 8*"-")
  for (d1k, d1v), (d2k, d2v) in zip(iteration1.items(), \
                                    iteration2.items()):
    value1 = d1v[metric]
    value2 = d2v[metric]
    diff = value1/value2
    print("{:25s}| {:>11.4f} | {:>11.4f} | {:>7.4f}".format(d1k, value1, value2, diff))
 

if __name__ == "__main__":
  if len(sys.argv) < 4:
    sys.exit(0)

  metric = sys.argv[1]
  file1 = sys.argv[2]
  file2 = sys.argv[3]

  with open(file1, "r") as json_data1, \
       open(file2, "r") as json_data2:
    data1 = json.load(json_data1)
    data1 = next(iter(data1.values())) 
    data2 = json.load(json_data2)
    data2 = next(iter(data2.values()))

    if "statistics" in data1:
      compare_statistics(data1, data2)
    else:
      compare_iteration0(data1, data2);
