/*
 * Server.h
 *
 *  Created on: Apr 4, 2021
 *      Author: benvh
 */

#ifndef COMPONENTS_SERVER_SERVER_H_
#define COMPONENTS_SERVER_SERVER_H_

class Server {
public:
	void StartServer(CommandInterface *itf);

	esp_err_t particle_handler(httpd_req_t* req);
	esp_err_t state_handler(httpd_req_t* req);
	esp_err_t color_handler(httpd_req_t* req);

private:
	CommandInterface *interface_;
};

#endif /* COMPONENTS_SERVER_SERVER_H_ */
