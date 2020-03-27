-- comp9311 19T3 Project 1
--
-- MyMyUNSW Solutions


-- Q1:
create or replace view Q1(unswid, longname)
as
    select unswid,longname from rooms rs 
    where rs.id in (select rf.room from room_facilities rf 
    where rf.facility = (select id from facilities where description = 'Air-conditioned'))
;

-- Q2:
create or replace view Q2(unswid,name)
as
    select unswid,name from people
    where id in (select staff from course_staff 
    where course in (select ce.course from course_enrolments ce 
    where ce.student = (select p.id from people p where name='Hemma Margareta')))
;




create or replace view Q31(c1id, c2id, sem)
as
    select c1.id, c2.id, c1.semester
    from courses c1 left join courses c2 on (c1.semester=c2.semester)
    where c1.subject=4897 and c2.subject=4878
;
--9024 HD intl  
create or replace view temp1(st, co, se)  
as
    select ce.student, ce.course, q31.sem
    from course_enrolments ce ,students ss, Q31 q31
    where ce.grade='HD' and ss.stype='intl' and ce.student = ss.id 
    and ce.course = q31.c1id 
;
--9311 HD intl
create or replace view temp2(st, co, se)
as
    select ce.student, ce.course, q31.sem
    from course_enrolments ce ,students ss, Q31 q31
    where ce.grade='HD' and ss.stype='intl' and ce.student = ss.id 
    and ce.course = q31.c2id
;
create or replace view stu
as
    select t1.st 
    from temp1 t1 left join temp2 t2 on (t1.se=t2.se)
    where t1.st=t2.st
;
 
-- Q3:
create or replace view Q3(unswid, name)
as 
    select p.unswid,p.name
    from people p,students ss
    where p.id=ss.id and  ss.id in (select * from stu)

;





-- Q4:
create or replace view Q4co(stu,numcour)
as
    select student ,count(course) from  course_enrolments 
    where mark is not null
    group by student
    ;
create or replace view Q4hd(stu,numnohd)
as
    select student, count(grade) from course_enrolments  
    where grade !='HD' and mark is not null 
    group by student
    ;  
create or replace view Q4num(stu,avghd)
as
    select q4c.stu, avg(q4c.numcour-q4h.numnohd)
    from Q4co q4c left join Q4hd q4h on (q4c.stu=q4h.stu)
    where q4c.numcour>=1
    group by q4c.stu
    ;  
create or replace view q4hdnum(stu,hd)
as 
    select student, count(*)
    from course_enrolments
    where grade = 'HD' and mark is not null
    group by student
;
create or replace view Q4(num_student)
as
    select count(*) from  q4hdnum q 
    where q.hd > (select avg(avghd) from Q4num)
    ;


--Q5:
create or replace view q5cmax(course_id, max_mark)
as
    select course, max(mark)
    from    course_enrolments
    group by course
    having count(mark)>=20
;
create or replace view q5semin(semes, min_mark)
as
    select cs.semester, min(qcm.max_mark)
    from q5cmax qcm, courses cs
    where qcm.course_id=cs.id
    group by cs.semester

;


create or replace view temp1(cid, max, sem, sub)
as
    select q5c.course_id, q5c.max_mark, cs.semester, cs.subject
    from q5cmax q5c left join courses cs on (q5c.course_id=cs.id)  
;

create or replace view temp2(se, sub)
as
    select t1.sem, t1.sub
    from temp1 t1 left join q5semin q5s on (q5s.semes=t1.sem)  
    where t1.max=q5s.min_mark
;

create or replace view Q5(code, name, semester)
as
    select ss.code,ss.name,sem.name 
    from subjects ss, temp2 t2, semesters sem 
    where ss.id=t2.sub and sem.id=t2.se
    ;



-- Q6:
create or replace view Q6strstu(stu)
as
    select distinct pens.student
    from semesters se, streams stre, stream_enrolments stens, program_enrolments pens
    where se.year=2010 and se.term='S1' and se.id=pens.semester and stre.name='Management' 
    and stre.id = stens.stream and stens.partof = pens.id 
;

create or replace view Q6st(student)
as
    select distinct q6s.stu
    from Q6strstu q6s,students ss
    where q6s.stu = ss.id  and ss.stype='local'
;

create or replace view Q6stu(student)
as
    select distinct ce.student 
    from course_enrolments ce, courses cs, subjects sus
    where ce.course = cs.id and sus.id= cs.subject and sus.offeredby = 112 
;

create or replace view Q6(num)
as
    select count(student)
    from Q6st
    where student not in (select student from Q6stu)     
;

-- Q7:

create or replace view Q7temp1(course_id, semester)
as
    select cs.id, cs.semester
    from courses cs
    where cs.subject = 1884 or cs.subject = 4897
;

create or replace view Q7temp2(course_id, mark, semester)
as
    select ce.course, ce.mark , qt1.semester
    from Q7temp1 qt1, course_enrolments ce 
    where qt1.course_id=ce.course
;

create or replace view Q7temp3(semester,ave)
as
    select qt2.semester, avg(qt2.mark)
    from Q7temp2 qt2
    where qt2.mark is not null
    group by qt2.semester
;
create or replace view Q7(year, term, average_mark)
as
    select ss.year, ss.term, round(qt3.ave,2)
    from semesters ss, Q7temp3 qt3
    where ss.id=qt3.semester
;


-- Q8: 


create or replace view Q8prop1(subid)
as
    select id from subjects 
    where code like 'COMP93__'
;
create or replace view Q8prop2(semid)
as
    select id from semesters
    where term like 'S%' and year >=2004 and year <=2013
;
create or replace view Q8prop3(subid,sem,courid)
as
    select cs.subject, cs.semester, cs.id
    from courses cs , Q8prop2 q82 
    where cs.semester=q82.semid
;
create or replace view Q8sub(subid)
as
    select subid
    from Q8prop3 
    group by subid
    having count(sem)=20
;
create or replace view Q8course(subid)
as
    select qs.subid
    from Q8sub qs, Q8prop1 q81
    where  qs.subid=q81.subid
;
create or replace view Q8course1(subid,courid)
as
    select qc.subid,cs.id
    from Q8course qc, courses cs, Q8prop2 q82
    where cs.subject=qc.subid and cs.semester=q82.semid
;
create or replace view Q8fail(stuid,courid,subid)
as
    select ce.student,q8c.courid ,q8c.subid
    from course_enrolments ce, Q8course1 q8c
    where ce.course =q8c.courid and ce.mark<=50
    order by ce.student
;
create or replace view Q8l
as
    select q.id
    from Q8stu q left join people p on (p.id=q.id)
    where p.name not like 'Eleanor%'
;
create or replace view Q8stu(id)
as
    select a.stuid
    from  Q8fail a
    where not exists(
        (select distinct b.subid
        from Q8course1 b)
        except 
        (select distinct c.subid 
        from Q8fail c
        where c.stuid=a.stuid)
    )
;
create or replace view Q8(zid, name)
as
    select distinct'z'||unswid,name
    from people
    where id in (select * from Q8l)
;
    

-- Q9:
create or replace view Q9con1(stuid)
as
    select p.id
    from people p, program_degrees pd, program_enrolments pe
    where pd.abbrev='BCs' and pe.program=pd.program and pe.student = p.id
;

create or replace view Qcon2(stuid)
as
    select 
    from Q9con1 q1, courses cs, course_enrolments ce, semesters ss
    where cs.semester=ss.id and ss.year=2010 and ss.term='S2'
    and cs.id=ce.course and q1.stuid=ce.student
;
create or replace view Q9(unswid, name)
as
    select p.unswid, p.name 
    from people p ,Qcon2 q2 
    where p.id=q2.stuid   
;

-- Q10:
create or replace view Q101(room)
as
    select id from rooms
    where rtype = 2
;
create or replace view Q102
as
    select cs.id 
    from courses cs
    where cs.semester in 
    (select ss.id from semesters ss where year=2011 and term='S1')
;
create or replace view Q103
as
    select * 
    from classes
    where course in (select * from Q102) and room in (select * from Q101)

;
create or replace view Q10count(room,num)
as
    select room,count(id) 
    from Q103
    group by room
;
create or replace view Q10rank(room,num)
as
    select q1.room, coalesce(qc.num,0)
    from Q10count qc right join Q101 q1 on (qc.room=q1.room)
;

create or replace view Q10r(unswid, longname, num)
as
    select m.unswid, m.longname,r.num
    from rooms m, Q10rank r
    where m.id=r.room
;
create or replace view Q10(unswid, longname, num, rank)
as
    select r.unswid, r.longname, r.num, rank() over(order by r.num desc) as rank
    from Q10r r
;
