-- PL/SQL Trigger
CREATE TABLE Library(
    rec_id INTEGER PRIMARY KEY,
    author VARCHAR2(50),
    title VARCHAR2(50)
);

CREATE TABLE LibAudit(
    record_id INTEGER,
    action VARCHAR2(10),
    author VARCHAR2(50),
    title VARCHAR2(50),
    old_author VARCHAR2(50),
    old_title VARCHAR2(50)
);

-- Create the trigger
CREATE OR REPLACE TRIGGER LibAuditTrigger
BEFORE DELETE OR UPDATE ON Library
FOR EACH ROW
BEGIN
    IF UPDATING THEN
        INSERT INTO LibAudit (record_id, action, author, old_author, title, old_title) VALUES (:OLD.rec_id, 'UPDATE', :NEW.author, :OLD.author, :NEW.title, :OLD.title);
    ELSIF DELETING THEN
        INSERT INTO LibAudit (record_id, action, author, title) VALUES (:OLD.rec_id, 'DELETE', :OLD.author, :OLD.title);
    END IF;
END;
/

INSERT INTO Library VALUES(1, 'Author 1', 'Book 1');
INSERT INTO Library VALUES(2, 'Author 2', 'Book 2');

UPDATE Library SET author = 'Author A' WHERE rec_id = 1;
DELETE FROM Library WHERE rec_id = 2;

SELECT * FROM LibAudit;

DROP TABLE LibAudit;
DROP TABLE Library;
