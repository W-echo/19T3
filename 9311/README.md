# introduction:

    All Universities require a significant information infrastructure in order to manage their affairs. 
    This typically involves a large commercial DBMS installation. UNSW's student information system sits behind the MyUNSW web site.  
    MyUNSW provides an interface to a PeopleSoft enterprise management system with an underlying Oracle database.
    This back-end system (Peoplesoft/Oracle) is often called NSS.
  
   Despite its successes, MyUNSW/NSS still has a number of deficiencies, including:
   
    •  no waiting lists for course or class enrolment
    •  no representation for degree program structures
    •  poor integration with the UNSW Online Handbook
  
  The second point prevents MyUNSW/NSS from being used for three important operations that would be extremely helpful to students in managing their enrolment:
  
    •  finding out how far they have progressed through their degree program, and what remains to be completed 
    •  checking what are their enrolment options for next semester (e.g. get a list of suggested courses) 
    •  determining when they have completed all of the requirements of their degree program and are eligible to graduate

  NSS contains data about student, courses, classes, pre-requisites, quotas, etc. but does not contain any representation of UNSW's degree program structures.  
  Without such information in the NSS database, it is not possible to do any of the above three. So, in 2007 the COMP9311 class devised a data model that could represent program requirements and rules for UNSW degrees. 
  This was built on top of an existing schema that represented all of the core NSS data (students, staff, courses, classes, etc.). The enhanced data model was named the MyMyUNSW schema.
  The MyMyUNSW database includes information that encompasses the functionality of NSS, the UNSW Online  Handbook,  and  the  CATS  (room  allocation)  database.  
  The MyMyUNSW data model, schema and database are described in a separate document.


# aims

    1. reading and understanding a moderately large relational schema (MyMyUNSW).
    2. implementing SQL queries and views to satisfy requests for information.
    3. The goal is to build some useful data access operations on the MyMyUNSW database. A theme of this project is "dirty data". 

# file instruction:

    summary.pdf records the table and its attributes
    description.pdf contains a description of the data model and SQL schema for the MyMyUNSW database.
    Question file includes problems need to be solved.
    test file is used for automatic detection.
