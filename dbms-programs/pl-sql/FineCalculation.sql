CREATE TABLE Borrower(RollNo number, Name varchar2(30), IssueDate date, Title varchar2(50), Status varchar2(1), PRIMARY KEY(RollNo));
INSERT INTO Borrower VALUES (46, 'John', '15-MAY-2023', 'Database Systems', 'I');
INSERT INTO Borrower VALUES (39, 'Emily', '02-APR-2022', 'Data Structures', 'I');
INSERT INTO Borrower VALUES (12, 'Alex', '19-JUL-2023', 'Programming in Python', 'I');
INSERT INTO Borrower VALUES (43, 'Jessica', '08-SEP-2022', 'C++ Programming', 'I');

SELECT * FROM Borrower;

CREATE TABLE Fine(RollNo number, BookIssueDate date, Amt number(7,2), FOREIGN KEY(RollNo) references Borrower(RollNo));

DECLARE
	BookIssueDate date;
	CurrentDate date;
	BookName varchar2(50);
	NoOfDays integer;
	inputRoll integer;
	Roll integer;
	fine number(7, 2);

BEGIN
	inputRoll := 46;
	SELECT IssueDate, Title INTO BookIssueDate, BookName FROM Borrower WHERE RollNo = inputRoll;
	DBMS_OUTPUT.PUT_LINE('Book Issue Date: ' || BookIssueDate);
	DBMS_OUTPUT.PUT_LINE('Book Title: ' || BookName);

	-- Calculate the no. of days
	NoOfDays := TRUNC(SYSDATE) - BookIssueDate;
	DBMS_OUTPUT.PUT_LINE(chr(10) || 'No. of days: ' || NoOfDays);

	IF NoOfDays > 15 AND NoOfDays <= 30 THEN
		fine := 5 * NoOfDays;
	ELSIF NoOfDays >= 30 THEN
		fine := 75 + 50 * (NoOfDays - 30);	-- the added 75 is the fine for the first 30 days
	ELSE
		fine := 0;
	END IF;
	DBMS_OUTPUT.PUT_LINE('Total Fine: ' || fine);

	UPDATE Borrower SET Status = 'R' WHERE RollNo = inputRoll;

	IF fine > 0 THEN
		INSERT INTO Fine VALUES(inputRoll, BookIssueDate, fine);
		SELECT * INTO Roll, CurrentDate, fine FROM Fine WHERE RollNo = inputRoll;

		DBMS_OUTPUT.PUT_LINE('Roll No: ' || Roll);
		DBMS_OUTPUT.PUT_LINE('Date: ' || CurrentDate);
		DBMS_OUTPUT.PUT_LINE('Fine Amount: ' || fine);
	END IF;
END;
/
SELECT * FROM Fine;
DROP TABLE Fine;
DROP TABLE Borrower;
