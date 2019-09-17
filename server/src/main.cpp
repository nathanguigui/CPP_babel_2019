//
// Created by lcomte on 17/09/2019.
//

#include <iostream>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}


int main(int ac, char **av)
{
    sqlite3 *db;
    int rc;
    std::string sql;
    char *zErrMsg = 0;

    rc = sqlite3_open("../database", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }
    sql = "SELECT Username, Password FROM user_db\n" \
          "\tWHERE Username ==";
    sql = sql + "\"";
    sql = sql + av[1];
    sql = sql + "\"";
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
    return 0;
}