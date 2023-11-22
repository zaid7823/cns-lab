-- Calculate Area of circle
CREATE TABLE Circle(rad integer, area number(7,2));

DECLARE
	radius Circle.rad%type;
	CircleArea Circle.area%type;
	startRange integer;
	endRange integer;
BEGIN
	startRange := :startRange;
	endRange := :endRange;

	FOR radius in startRange..endRange LOOP
		CircleArea := 3.14159 * radius * radius;
		INSERT INTO Circle VALUES(radius, CircleArea);
	END LOOP;
END;
