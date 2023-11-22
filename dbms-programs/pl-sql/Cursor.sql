-- PL/SQL Cursor

CREATE TABLE Roll1(Roll integer, Name varchar2(50));
INSERT INTO Roll1(1, 'A');
INSERT INTO Roll1(3, 'C');
INSERT INTO Roll1(5, 'E');
INSERT INTO Roll1(7, 'G');

CREATE TABLE Roll2(Roll integer, Name varchar2(50));
INSERT INTO Roll2(2, 'B');
INSERT INTO Roll2(4, 'D');
INSERT INTO Roll2(6, 'F');

CREATE TABLE NewRoll(NewRollNo integer, NewName varchar2(50));

DECLARE
    -- declare two records for both the existing tables
    row1 Roll1%rowtype;
    row2 Roll2%rowtype;
    CURSOR o_cur1 IS SELECT * FROM Roll1 ORDER BY Roll;
    CURSOR o_cur2 IS SELECT * FROM Roll2 ORDER BY Roll;

BEGIN
    OPEN o_cur1;
    OPEN o_cur2;
    FETCH o_cur1 INTO row1;
    FETCH o_cur2 INTO row2;

    LOOP
        EXIT WHEN o_cur1%NOTFOUND OR o_cur2%NOTFOUND;

        IF row1.Roll = row2.Roll THEN
            INSERT INTO NewRoll VALUES(row1.Roll, row1.Name);
            FETCH o_cur1 INTO row1;
            FETCH o_cur2 INTO row2;
        ELSIF row1.Roll > row2.Roll THEN
            INSERT INTO NewRoll VALUES(row2.Roll, row2.Name);
            FETCH o_cur2 INTO row2;
        ELSE
            INSERT INTO NewRoll VALUES(row1.Roll, row1.Name);
            FETCH o_cur1 INTO row1;
        END IF;
    END LOOP;

    LOOP
        EXIT WHEN o_cur1%NOTFOUND;
        INSERT INTO NewRoll VALUES(row1.RollNo, row1.Name);
        FETCH o_cur1 INTO row1;
    END LOOP;

    LOOP
        EXIT WHEN o_cur2%NOTFOUND;
        INSERT INTO NewRoll VALUES(row2.RollNo, row2.Name);
        FETCH o_cur2 INTO row2;
    END LOOP;

    CLOSE o_cur1;
    CLOSE o_cur2;
END;
/
