# Objectives:
  to implement a simple search engine based on the well known PageRank algorithm (simplified). 
  to give you further practice with C and advanced data structures (Graph and BST ADTs)


# tasks in summary:
  1. Calculate PageRanks: You need to create a graph structure that represents a hyperlink structure of given collection of "web pages" and for each page (node in your graph) calculate PageRank value and other graph properties. 
  2. Inverted Index: You need to create "inverted index" that provides a list of pages for every word in a given collection of pages. 
  3. Search Engine: Your search engine will use the given inverted index to find pages where query term(s) appear and rank these pages using their PageRank values (see below for more details)



codes in file:
# partA: pagerank.c                
      input: collection.txt      recording urls, eg: url12, url23...
      output: pagerankList.txt   one line per url, it includes out degrees (number of out going links) for each url, along with its PageRank value.
                                 eg: url31, 3, 0.2623546

# partB: invertedIndex.c       
      input: collection.txt
      output:invertedIndex.txt   One line per word, words should be alphabetically ordered, using ascending order. Each list of urls (for a single word) should be alphabetically ordered, using ascending order.
                                 eg:    design  url2 url25 url31 url61     
                                        mars  url101 url25 url31     
                                        vegetation  url31 url61
 # partC: searchPagerank.c   
      input: given search terms (words) as commandline arguments, eg: mars, design
      output: pages with one or more search terms and outputs (to stdout) top 30 pages in descending order of number of search terms found and then within each group, descending order of PageRank.
