-- Named Procedure
CREATE TABLE Stud_Marks (Roll integer, Name varchar2(50), totalMarks integer);
INSERT INTO Stud_Marks VALUES (1, 'John', 1450);
INSERT INTO Stud_Marks VALUES (2, 'Jack', 877);
INSERT INTO Stud_Marks VALUES (3, 'Sean', 654);

CREATE TABLE Result (Roll integer, Name varchar2(50), class varchar2(30));

DECLARE
	v_roll integer;
	v_marks integer;
	v_class varchar2(50);
	v_name varchar2(50);
	inputRollNo integer;

Procedure ClassDistribution IS
BEGIN
	inputRollNo := 2;
	SELECT Roll, Name, totalMarks INTO v_roll, v_name, v_marks FROM Stud_Marks WHERE Roll = inputRollNo;

	IF v_marks <= 1500 AND v_marks > 990 THEN
		INSERT INTO Result VALUES(v_roll, v_name, 'Distinction');

	ELSIF v_marks <= 990 AND v_marks > 900 THEN
		INSERT INTO Result VALUES(v_roll, v_name, 'First Class');

	ELSIF v_marks <= 900 AND v_marks > 825 THEN
		INSERT INTO Result VALUES(v_roll, v_name, 'Second Class');

	ELSE
		INSERT INTO Result VALUES(v_roll, v_name, 'Other');

	END IF;
END;

BEGIN
	ClassDistribution;
END;
/
  
SELECT * FROM Result;
DROP TABLE Result;
DROP TABLE Stud_Marks;
