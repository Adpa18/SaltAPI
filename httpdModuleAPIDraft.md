# HTTPD Module API

## Miscellaneous

* Communication session (abstract socket communication with the client with adding TLS)
	* (socket + tls) abstraction

* To generate (on-the-fly) and send HTTP response representation to client: HTTP message class write to communcation session #overide<<)

* Philosophy: I just parse a HTTP request, its body is gziped -> I add an entity decompression module after me

* The processing line is an objet with actions like: addModuleCallAfterMe, addModuleCallAfterModuleType, ...

* What is multi-threaded ?

* The modules called during the "HTTP message processing line" received as objects the request, the response, and the processing line reference.

## Workflow

* HTTPD load module (moduleLoader)
* core module (core)
	* init server logging (logging)
	* Create default HTTP message (HTTPMessageSkel)
	* parse server config file (configParser)

	* init network stack + wait for a client to connect (network)
	* open communication session with or without TLS (communicationSession)
	* Add client request to processing queue #LILO (queueHandler)
		* generate generic processing line. (Ex. I'll need to parse the request, then look at the headers, generate representation and send) (processLineGenerator)

			* PARSE
				* HTTP message parser (parseHTTPMessage)
				* Decode ressource URL (URLEncode)
			* INSPECT
				* inspect HTTP message method + headers and add appropriate modules in the processing line (headerInspector)
			* DECAPSULATE (#makeItHumanReadable)
				* decompress entity (compress)
			* GENERATE REPRESENTATION
				* generate the (entity) representation (representationGenerator)
					* access file content on filesystem (+ directory browsing) (fileServe)
					* execute CGI module (ohMyCGI)
						* run backend PHP script (PHPCGI)
					* format the entity (entityContentTypeFormater)
						* Render ressource in JSON (Ex. application/json) (JSONFormater)
			* ENCAPSULATE
				* compress entity (compress)
				* encode via Transfert-Encoding header (Ex. split body in chunks) (transfertEncoding)
			* SEND
				* send the HTTP message to communication session (network)

	* close communication session (network)

## Module Types

### Server category

* logging module

* HTTP message skel module
* config loader module
* network module
	* raise network
	* establish communication sessions

* file access module
* compression module
* CGI module

* HTTP message queue module

### HTTP protocol category (#wordProcessing)

* HTTP message parsing module
* HTTP message validator module
* HTTP message header inspector module
* HTTP message entity formating module
* URL encode module
* HTTP message entity encoding

### File structure

httpd
httpd\_conf.json
modules/
	core.so
	network.so
	fileServe.so
