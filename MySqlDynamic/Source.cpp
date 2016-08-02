/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/*
Include directly the different
headers from cppconn/ and mysql_driver.h + mysql_util.h
(and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main(void)
{
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;

	/* Create a connection */
	driver = get_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "1234");

	/* Connect to the MySQL test database */
	con->setSchema("test");
	stmt = con->createStatement();

	/*
	stmt->execute("USE test");
	stmt->execute("DROP TABLE IF EXISTS test");
	stmt->execute("CREATE TABLE test(id INT, label CHAR(1))");
	stmt->execute("INSERT INTO test(id, label) VALUES (1, 'a')");
	*/

	res = stmt->executeQuery("SELECT id, label FROM test ORDER BY id ASC");
	while (res->next()) {
		// You can use either numeric offsets...
		cout << "id = " << res->getString("id"); // getInt(1) returns the first column
										   // ... or column names for accessing results.
										   // The latter is recommended.
		cout << ", label = '" << res->getString("label") << "'" << endl;
	}

	delete res;
	delete stmt;
	delete con;

	return 0;
}