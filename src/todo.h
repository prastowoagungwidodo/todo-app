// Todo Main function
// Kelompok IV UNUSIA

#ifndef TODO_H
#define TODO_H

#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <time.h>

#include <mongoose.h>
#include <sqlite3.h>
#include <jansson.h>

/* URL's */
#define TODOS_URL "/todos"
#define TODO_UPDATE_REGEX "^\\/todos\\/[[:digit:]]"

/**
* Karena untuk membuka prot 80 membutuhkan super user privileges,
* maka kami buka port 3000 yang dapat dilakukan dari limited user.
*/
#define DEFAULT_HTTP_PORT "3000"

extern sqlite3 *db;
extern struct mg_server *server;

enum log_level {
    LOG_INFO,
    LOG_ERROR
};

// Biar warna warni di terminalnya :D
#define LOG_INFO_TPL  "\x1B[0;32m[%s] %s\x1B[0m\n"
#define LOG_ERROR_TPL "\x1B[0;31m[%s] %s\x1B[0m\n"

/**
 * Event handler mongoose
 */
extern int event_handler (struct mg_connection *conn, enum mg_event ev);

/**
 * Initialize http server dan database
 */
extern void initialize (char *http_port);

/**
 * Terminate http server dan database
 */
extern void term (void);

/**
 * Logs
 */
extern void log_line(char *content, enum log_level level);

//
// Actions
//

/**
 * list tasks
 * GET /todos
 */
extern void todos_index (struct mg_connection *conn);

/**
 * menambahkan task
 * POST /todos
 */
extern void todos_create (struct mg_connection *conn);

/**
 * update task
 * PUT /todo/:id
 */
extern void todos_update (struct mg_connection *conn, int todo_id);

/**
 * menghapus task
 * DELETE /todo/:id
 */
extern void todos_delete (struct mg_connection *conn, int todo_id);

/**
 * menampilkan task berdasarkan id
 * GET /todo/:id
 */
extern void todos_show (struct mg_connection *conn, int todo_id);

//
// Model
//

#define TODO_STATUS_DEFAULT   0
#define TODO_STATUS_COMPLETED 1

/**
 * Mengambil semua data tasks
 * @return json_t (array)
 */
extern json_t *todo_find_all (void);

/**
 * menyimpan task ke dalam database
 * @param char *text (konten)
 * @return int (generated todo id)
 */
extern int todo_create (char *text);

/**
 * menampilkan task berdasarkan id
 * @param int todo_id
 * @return json_t (todo)
 */
extern json_t *todo_find_by_id (int todo_id);

/**
 * update task
 * @param int  todo_id
 * @param json_t *attributes
 * @return json_t * (updated todo)
 */
extern json_t *todo_update_attributes (int todo_id, json_t *attributes);

/**
 * delete task
 * @param id todo_id
 * @return int (0 == ok, -1 == sql error)
 */
extern int todo_destroy(int todo_id);

#endif
