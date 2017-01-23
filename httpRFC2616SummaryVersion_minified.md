# HTTP (Hypertext Transfer Protocol)

## Intro

* Application-level protocol. (OSI model layer 7)
* First http version: HTTP/0.9
* HTTP/1.0: RFC 1945
* HTTP/1.1: RFC 2616 (1999)
* URI: Uniform Resource Identifier
* URL: Uniform Resource Locator
* URN: Uniform Resource Name
* HTTP request: methods + ressource UR{I, L, N} + headers
* Messages are passed in a format similar to that used by Internet mail as defined by the Multipurpose Internet Mail Extentions (MIME)
* HTTP also used as a generic protocol for communication between user agents and proxies/gateways to other Internet systems (SMTP, FTP...)
* MIME (Multipurpose Internet Mail Extensions) is an Internet standard that extends the format of email to support:
	* Text in character sets other than ASCII
	* Non-text attachments: audio, video, images, application programs etc.
	* Message bodies with multiple parts
	* Header information in non-ASCII character sets

## Terminology

**See RFC 2616 section 1.3**

## Overall Operation

* The HTTP protocole is a request/response protocol.
* Client send request to server with:
	* a request method (Ex. `POST`)
	* URI (Ex. `/` or `/index.html`)
	* the protocol version (Ex. `HTTP/1.1`)
	* request modifiers (Ex. `Host: www.perdu.com`)
	* client information (Ex. `User-Agent: curl/7.51.0`)
	* possible body (Ex. `password=QuandLeDouteMHabite`)
* Server responds with:
	* a status line, including message's protocol version and a success or error code (Ex. `HTTP/1.1 200 OK`)
	* server information (Ex. `Server: Apache`)
	* entity metainformation (Ex. `Content-Length: 204`)
	* possible entity-body content (Ex. `<html><head><title>Vous Etes Perdu ?</title></head></html>`)

Ex.
```text
curl -vvv www.perdu.com
> GET / HTTP/1.1
> Host: www.perdu.com
> User-Agent: curl/7.51.0
> Accept: */*
>
< HTTP/1.1 200 OK
< Date: Fri, 16 Dec 2016 09:12:47 GMT
< Server: Apache
< Last-Modified: Thu, 02 Jun 2016 06:01:08 GMT
< ETag: "cc-5344555136fe9"
< Accept-Ranges: bytes
< Content-Length: 204
< Vary: Accept-Encoding
< Content-Type: text/html
<
<html><head><title>Vous Etes Perdu ?</title></head><body><h1>Perdu sur l'Internet ?</h1><h2>Pas de panique, on va vous aider</h2><strong><pre>    * <----- vous &ecirc;tes ici</pre></strong></body></html>
```

* Intermediaries can be present in the request/response chain:
	* proxy (a forwarding agent, receiving requests for a URI in its absolute form, rewriting all or part of the message, and forwarding the reformatted request toward the server identified by the URI.)
	* gateway (a receiving agent, acting as a layer above some other server(s) and, if necessary, translating the requests to the underlying server's protocol.)
	* tunnel (a relay point between two connections without changing the messages; tunnels are used when the communication needs to pass through an intermediary (such as a firewall) even when the intermediary cannot understand the contents of the messages.)
* If not tunnel -> may employ an internal cache for handling requests.
	* Not all responses are usefully cacheable
	* Some requests may contain modifiers which place special requirements on cache behavior.
* HTTP communication usually takes place over TCP/IP connections
	* can be Implemented on top of any other protocol on the Internet as long as the transport is reliable. (a.k.a not UDP)
* The default port is TCP 80.
* A connection may be used for one or more request/response exchanges.

More explanations [HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Session).

## Basic grammar rules

**See RFC 2616 section 2.2**

* HTTP/1.1 defines the sequence CR LF (`\r\n`) as the end-of-line marker for all protocol elements except the entity-body.
* Ex. `echo -ne 'GET / HTTP/1.1\r\nHost: www.perdu.com\r\n\r\n' | nc www.perdu.com 80 | cat -e`
* Ex. `echo -ne 'GET\t/\tHTTP\t/\t1\t.\t1\r\nHost\t:\twww.perdu.com\r\n\r\n' | nc www.perdu.com 80 | cat -e`

## HTTP Version

* HTTP protocol version named like `<major>.<minor>`.
* The `<minor>` number is incremented when the changes made to the protocol add features which do not change the general message parsing algorithm.
* The `<major>` number is incremented when the format of a message within the protocol is changed.
* Ex. `HTTP/2.4` < `HTTP/2.13` < `HTTP/12.3`
* The version of an HTTP message is indicated by an HTTP-Version field in the first line of the message. (Ex. `HTTP/1.1`)
* `HTTP-Version   = "HTTP" "/" 1*DIGIT "." 1*DIGIT`
* The HTTP version of an application is the highest HTTP version for which the application is at least conditionally compliant.

### Uniform Resource Identifiers (URI)

* URIs have been known by many names:
	* URIs
	* WWW addresses
	* Universal Document Identifiers
	* Universal Ressource Identifiers
	* Uniform Resource Locator (URL) + Names (URN)
* URI are simply formatted strings which identify -- via name, location, or any other characteristic -- a ressource.
* URIs in HTTP can be represented in absolute form or relative to some known base URI.
* The HTTP protocol does not place any a priori limit on the length of a URI.
* A server SHOULD return 414 (Request-URI Too Long) status if a URI is longer than the server can handle

Examples can be found [HERE](https://en.wikipedia.org/wiki/Uniform_Resource_Identifier).
More explanations [HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/Identifying_resources_on_the_Web).

### HTTP URL

* `http_URL = "http:" "//" host [ ":" port ] [ abs_path [ "?" query ]]`
* If the port is empty or not given, port 80 is assumed
* The use of IP addresses in URLs SHOULD be avoided whenever possible.
* If the `abs_path` is not present in the URL, it MUST be given as "/" when used as a Request-URI for a resource.

More explanations [HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/Identifying_resources_on_the_Web).

### URI Comparison

* Comparing two URIs -> SHOULD be case-sensitive octet-by-octet comparison of the entire URIs
* Exceptions:
	* A port that is empty or not given is equivalent to the default port
	* Comparisons of host names MUST be case-insensitive
	* Comparisons of scheme names MUST be case-insensitive
	* An empty `abs_path` is equivalent to an `abs_path` of "/"
* Characters other than those in the "reserved" and "unsafe" sets (see RFC 2396 [42]) are equivalent to their ""%" HEX HEX" encoding.
* For example, the following three URIs are equivalent:
```text
http://abc.com:80/~smith/home.html
http://ABC.com/%7Esmith/home.html
http://ABC.com:/%7esmith/home.html
```

## Date/Time Format

### Full date

* 3 historically allowed formats for the date/time stamps:
	* `Sun, 06 Nov 1994 08:49:37 GMT  ; RFC 822, updated by RFC 1123`
	* `Sunday, 06-Nov-94 08:49:37 GMT ; RFC 850, obsoleted by RFC 1036`
	* `Sun Nov  6 08:49:37 1994       ; ANSI C's asctime() format`
* The first format is preferred as an Internet standard and represents a fixed-length subset
* MUST accept all three formats
* MUST only generate the RFC 1123 format for representing HTTP-date values in header fields.
* All HTTP date/time stamps MUST be represented in Greenwich Mean Time (GMT), without exception.
	* GMT is exactly equal to UTC (Coordinated Universal Time).
	* GMT MUST be assumed when reading the asctime format.
* HTTP-date is case sensitive

**See RFC 2616 section 3.3.1 for BNF lovers**

## Charset

* HTTP character sets are identified by case-insensitive tokens.
* The complete set of tokens is defined by the IANA Character Set registery
* `charset = token`
* Ex. ` Content-Type: text/html; charset=utf-8`

Examples can be found [HERE](https://www.iana.org/assignments/character-sets/character-sets.xhtml).

## Content Codings

* `content-encoding = token`
* All content-coding values are case-insensitive
* HTTP/1.1 uses content-encoding values in header fields:
	* `Accept-Encoding`
	* `Content-Encoding`
* The Internet Assigned Numbers Authority (IANA) acts as a registry for content-coding value tokens.
* Initially, the regisrty contains the following tokens:
	* gzip (An encoding format produced by the file compression program "gzip" (GNU zip))
	* compress (The encoding format produced by the common UNIX file compression program "compress".)
	* deflate (The "zlib" format in combination with the "deflate" compression mechanism)
	* identity (The default (identity) encoding; the use of no transformation whatsoever.)

* Ex. `Content-Encoding: gzip`

Examples can be found [HERE](https://www.iana.org/assignments/http-parameters/http-parameters.xhtml).
More explanations [HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Content-Encoding).

## Transfert Codings

* The Transfer-Encoding header specifies the form of encoding used to safely transfer the entity to the user.

**See RFC 2616 section 3.6 for BNF**

* This differs from a content coding in that the transfer-coding is a property of the message, not of the original entity.
* All transfer-coding values are case-insensitive.
* The Internet Assigned Numbers Authority (IANA) acts as a registry for transfer-coding value tokens (initially:)
	* "chunked"
	* "identity"
	* "gzip"
	* "compress"
	* "deflate"
* A server which receives an entity-body with a transfer-coding it does not understand SHOULD:
	* return 501 (Unimplemented)
	* close the connection.
* A server MUST NOT send transfer-codings to an HTTP/1.0 client.

* Ex. `Transfer-Encoding: gzip, chunked`

Examples can be found [HERE](https://www.iana.org/assignments/http-parameters/http-parameters.xhtml)
More explanations [HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Transfer-Encoding)

### Chunked Transfert Coding

* Data can sent in blocks without knowing the whole data size to transmit.

More explanations [HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Transfer-Encoding#Examples)

## Media Types

* HTTP uses Internet Media Types in the header fields:
	* Content-Type
	* Accept header fields

**See RFC 2616 section 3.7 for BNF**

* Parameters MAY follow the type/subtype in the form of `attribute/value` pairs.
* The type, subtype, and parameter attribute names are case-insensitive.
* Parameter values might or might not be case-sensitive, depending on the semantics of the parameter name.
* Linear white space MUST NOT be used between:
	* the type
	* subtype
	* an attribute and its value.
* Media-type values are registered with the Internet Assigned Number Authority (IANA).

Examples can be found [HERE](https://www.iana.org/assignments/media-types/media-types.xml)
More explanations [HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_Types)

### Canonicalization and text defaults

* Media subtypes of the "text" type use CRLF as the text line break.
	* HTTP applications MUST accept CRLF, bare CR, and bare LF as being representative of a line break in text media received.
	* Applies only to text media in the entity-body
		* a bare CR or LF MUST NOT be substituted for CRLF within any of the HTTP control structures (such as header fields and multipart boundaries).
* When no explicit charset parameter is provided by the sender, media subtypes of the "text" type are defined to have a default charset value of "ISO-8859-1" when received.

### Multipart Types

* "multipart" types: encapsulations of one or more entities within a single message-body.
* The message body is itself a protocol element and MUST therefore use only CRLF to represent line breaks between body-parts.
* Used for example when a client wants to upload multiples files on a server.

More explanations [HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/MIME_types#multipartform-data)

## Product Tokens

* Used to allow communicating applications to identify themselves by software name and version.
* Most fields using product tokens also allow sub-products which form a significant part of the application to be listed, separated by white space.
* By convention, the products are listed in order of their significance for identifying the application.

**See RFC 2616 section 3.8 for BNF**

* Product tokens SHOULD be short and to the point.
* They MUST NOT be used for advertising or other non-essential information.
* Although any token character MAY appear in a product-version, this token SHOULD only be used for a version identifier.

* Ex: `Server: Apache/0.8.4`, `User-Agent: CERN-LineMode/2.15 libwww/2.17b3`

## Quality Values

* HTTP content negotiation uses short "floating point" numbers to indicate the relative importance ("weight") of various negotiable parameters. 
* A weight is normalized to a real number in the range 0 through 1, where 0 is the minimum and 1 the maximum value.
* If a parameter has a quality value of 0, then content with this parameter is 'not acceptable' for the client.

**See RFC 2616 section 3.9 for BNF**

More explanations [HERE](https://developer.mozilla.org/en-US/docs/Glossary/Quality_values)

## Language Tags

* A language tag identifies a natural language spoken, written, or otherwise conveyed by human beings for communication of information to other human beings.
* HTTP uses language tags with:
	* `Accept-Language`
	* `Content-Language`
* All tags are case-insensitive.
* The name space of language tags is administered by the IANA.

**See RFC 2616 section 3.10 for BNF**

* Ex. `en`, `en-US`

## Entity Tags

* Entity tags are used for comparing two or more entities from the same requested resource.
* HTTP/1.1 uses entity tags in the following header fields:
	* ETag
	* If-Match
	* If-None-Match
	* If-Range

**See RFC 2616 section 3.11 for BNF**

* It is one of several mechanisms that HTTP provides for web cache validation
* An entity tag MUST be unique across all versions of all entities associated with a particular resource.
* Ex. `ETag: "686897696a7c876b7e"` and `If-None-Match: "686897696a7c876b7e"`

More explanations [HERE](https://en.wikipedia.org/wiki/HTTP_ETag)

## Range Units

* Client can request that only part (a range of) the response entity be included within the response.
* Client uses range units in the header fields:
	* `Range`
	* `Content-Range`

**See RFC 2616 section 3.12 for BNF**

* The only range unit defined is "bytes".
* Implementations MAY ignore ranges specified using other units.

More explanations [HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Status/206)

## HTTP Message Types

* HTTP messages consist of requests from client to server and responses from server to client.
* Request and Response messages use the generic message format of RFC 822 for transferring entities (the payload of the message).
* Both types of message consist of:
	* a start-line
	* zero or more header fields (also known as "headers")
	* an empty line (i.e., a line with nothing preceding the CRLF) indicating the end of the header fields
	* and possibly a message-body.

**See RFC 2616 section 4.1 for BNF**

* Servers SHOULD ignore any empty line(s) received where a Request-Line is expected.
	* If the server is reading the protocol stream at the beginning of a message and receives a CRLF first, it should ignore the CRLF.

More explanations [HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Messages)

## Message Headers

* HTTP header fields can be:
	* general-header (Headers applying to both requests and responses but with no relation to the data eventually transmitted in the body.)
	* request-header (Headers containing more information about the resource to be fetched or about the client itself.)
	* response-header (Headers with additional information about the response, like its location or about the server itself (name and version etc.).)
	* entity-header (Headers containing more information about the body of the entity, like its content length or its MIME-type.)
* Each header field consists of a name followed by a colon (":") and the field value.
* Field names are case-insensitive.

**See RFC 2616 section 4.2 for BNF**

More explanations [HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers)

## Message Body

* Transfer-Encoding MUST be used to indicate any transfer-codings applied by an application.
* The presence of a message-body in a request is signaled by the inclusion of one of those header fields:
	* `Content-Length`
	* `Transfer-Encoding`
* A message-body MUST NOT be included in a request if the specification of the request method does not allow sending an entity-body in requests.
* All responses to the HEAD request method MUST NOT include a message-body
* All 1xx (informational), 204 (no content), and 304 (not modified) responses MUST NOT include a message-body.
* All other responses do include a message-body, although it MAY be of zero length.

More explanations [HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Messages)

## Message Length

* The transfer-length of a message is the length of the message-body as it appears in the message in decimal number of octets.
	* that is, after any transfer-codings have been applied.
* If a request contains a message-body and a `Content-Length` is not given, the server SHOULD respond:
	* 400 (bad request)
	* or 411 (length required)
* Ex. `Content-Length: 204`

# Request

**See RFC 2616 section 5 for BNF**

## Request-Line

* The Request-Line:
	* begins with a method token. (Ex. `POST`)
	* followed by the Request-URI
	* and the protocol version
	* ending with a CRLF.
* `Request-Line   = Method SP Request-URI SP HTTP-Version CRLF`

* Ex. `POST /contact_form.php HTTP/1.1`

### Method

* The method is case-sensitive.
* HTTP 1.1 methods :
	* `OPTION`: describe the communication options for the target resource.
	* `GET`: requests a representation of the specified resource.
	* `HEAD`: asks for a response identical to that of a `GET` request, but without the response body.
	* `POST`: submit an entity to the specified resource, often causing a change in state or side effects on the server.
	* `PUT`: replaces all current representations of the target resource with the request payload.
	* `DELETE`: delete the specified resource.
	* `TRACE`: performs a message loop-back test along the path to the target resource.
	* `CONNECT`: establishes a tunnel to the server identified by the target resource.
* The list of methods allowed by a resource can be specified in an Allow header field.
* The return code of the response always notifies the client whether a method is currently allowed on a resource.
* Server SHOULD return the status code:
	* 405 (Method Not Allowed) if the method is known by the origin server but not allowed for the requested resource.
	* 501 (Not Implemented) if the method is unrecognized or not implemented by the origin server.
* The methods GET and HEAD MUST be supported.
	* All other methods are OPTIONAL.

### Request-URI

* `Request-URI    = "*" | absoluteURI | abs_path | authority`
* The asterisk `*` means that the request does not apply to a particular resource (Ex. `OPTIONS * HTTP/1.1`)
* Absolute path must be at least `/`

* Ex.
```text
$ nc www.perdu.com 80

OPTIONS / HTTP/1.1
Host: www.perdu.com

HTTP/1.1 200 OK
Date: Fri, 30 Dec 2016 16:24:46 GMT
Server: Apache
Allow: POST,OPTIONS,GET,HEAD
Vary: Accept-Encoding
Content-Length: 0
Content-Type: text/html
```

## The Resource Identified by a Request

* The exact resource identified by an Internet request is determined by examining:
	* the Request-URI
	* the Host header field
* An origin server that does differentiate resources based on the host requested (virtual hosts) MUST use the following rules:
	* If Request-URI is an absoluteURI -> Host header field value in the request MUST be ignored.
	* If the Request-URI is not an absoluteURI and request includes a Host header field -> the host is determined by the Host header field value.
	* If the host as determined by rule 1 or 2 is not a valid host on the server, the response MUST be a 400 (Bad Request) error message.

* Ex.
```text
$ nc www.perdu.com 80

GET http://www.perdu.com HTTP/1.1
Host: www.google.com

HTTP/1.1 200 OK
[...]
```

## Request Header Fields

* Allow the client to pass additional information:
	* about the request
	* about the client

**See RFC 2616 section 5.3 for BNF**

# Response

**See RFC 2616 section 6 for BNF**

## Status-Line

* `Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF`

### Status Code and Reason Phrase

* The Status-Code element is a 3-digit integer result code
* The Reason-Phrase is intended to give a short textual description of the Status-Code.
* The first digit of the Status-Code defines the class of response.
* The last two digits do not have any categorization role.
* There are 5 values for the first digit:
	* 1xx: Informational - Request received, continuing process
	* 2xx: Success - The action was successfully received, understood, and accepted
	* 3xx: Redirection - Further action must be taken in order to complete the request
	* 4xx: Client Error - The request contains bad syntax or cannot be fulfilled
	* 5xx: Server Error - The server failed to fulfill an apparently valid request

**See RFC 2616 section 6.1.1 for BNF**

* Applications MUST:
	* understand the class of any status code (as indicated by the first digit)
	* treat any unrecognized response as being equivalent to the x00 status code of that class.
		* with the exception that an unrecognized response MUST NOT be cached.

## Response Header Fields

* Allow the server to pass additional information about the response which cannot be placed in the Status-Line.

**See RFC 2616 section 6.2 for BNF**

* Unrecognized header fields are treated as entity-header fields.
* Ex. `Content-Type: text/html`

# Entity

* Request and Response messages MAY transfer an entity if:
	* not otherwise restricted by the request method
	* or response status code

## Entity Header Fields

* Entity-header fields define metainformation about the entity-body.
* Some of this metainformation is OPTIONAL.
* Unrecognized header fields SHOULD be ignored by the recipient.

## Entity Body

* The entity-body (if any) sent with an HTTP request or response is in a format and encoding defined by the entity-header fields.
* `entity-body    = *OCTET`
* only present in a message when a message-body is present.
* The entity-body is obtained from the message-body by decoding any `Transfer-Encoding`.

### Type

* When an entity-body is included with a message, the data type of that body is determined via the header fields Content-Type and Content-Encoding.

**See RFC 2616 section 7.2.1 for BNF**

* Content-Type specifies the media type of the underlying data.
* Messages containing an entity-body SHOULD include a Content-Type header field defining the media type of that body.
	* If and only if the media type is not given by a Content-Type field, the recipient MAY attempt to guess the media type via inspection of its content and/or the name extension(s) of the URI used to identify the resource.
	* If the media type remains unknown, the recipient SHOULD treat it as type "application/octet-stream".

### Entity Length

The entity-length of a message is the length of the message-body before any transfer-codings have been applied.

# Connections

## Persistent Connections

### Purpose

* Persistent HTTP connections have a number of advantages:
	* By opening and closing fewer TCP connections, CPU time is saved in routers and hosts and memory used for TCP protocol control blocks can be saved in hosts.
	* HTTP requests and responses can be pipelined on a connection.
		* Pipelining allows a client to make multiple requests without waiting for each response.
	* Network congestion is reduced by reducing the number of packets caused by TCP opens.
	* Latency on subsequent requests is reduced since there is no time spent in TCP's connection opening handshake.
	* HTTP can evolve more gracefully, since errors can be reported without the penalty of closing the TCP connection.

* HTTP implementations SHOULD implement persistent connections.

### Overall Operation

* Persistent connections provide a mechanism by which a client and a server can signal the close of a TCP connection using the Connection header field.

#### Negotiation

* If either the client or the server sends the close token in the Connection header, that request becomes the last one for the connection.
* In order to remain persistent, all messages on the connection MUST have a self-defined message length.

* Ex. `Connection: close`

#### Pipelining

* Client can send multiple requests without waiting for each response.
* A server MUST send its responses to those requests in the same order that the requests were received.

### Parctical considerations

* Servers will usually have some time-out value beyond which they will no longer maintain an inactive connection.
* When a client or server wishes to time-out it SHOULD issue a graceful close on the transport connection.
* A client, server, or proxy MAY close the transport connection at any time.
* Clients, servers, and proxies MUST be able to recover from asynchronous close events.
* Servers SHOULD always respond to at least one request per connection, if at all possible.
* Servers SHOULD NOT close a connection in the middle of transmitting a response.

# Method Definitions

## Safe and Idempotent Methods

### Safe Methods

* An HTTP method is safe if it doesn't alter the state of the server. In other words, a method is safe if it leads to a read-only operation.
* The convention has been established that the GET and HEAD and OPTION methods SHOULD NOT have the significance of taking an action other than retrieval.
* These methods ought to be considered "safe".

* common safe methods: GET, HEAD, OPTIONS
* common unsafe methods: PUT, DELETE, POST

More explanations [HERE](https://developer.mozilla.org/en-US/docs/Glossary/safe).

## OPTION

* This method allows the client to determine:
	* options and/or requirements associated with a resource
	* capabilities of a server
	* initiating a resource retrieval
* Responses to this method are not cacheable.
* If the Request-URI is an asterisk ("\*"), the OPTIONS request is intended to apply to the server in general
* It does nothing beyond allowing the client to test the capabilities of the server.
* If the Request-URI is not an asterisk, the OPTIONS request applies only to the options that are available when communicating with that resource.
* A 200 response SHOULD include any header fields that indicate optional features implemented by the server and applicable to that resource (e.g., Allow)

Ex.
```text
OPTIONS /index.html HTTP/1.1
OPTIONS * HTTP/1.1
```

Ex.
```text
$ curl -X OPTIONS http://example.org -i

HTTP/1.1 200 OK
Allow: OPTIONS, GET, HEAD, POST
Cache-Control: max-age=604800
Date: Thu, 13 Oct 2016 11:45:00 GMT
Expires: Thu, 20 Oct 2016 11:45:00 GMT
Server: EOS (lax004/2813)
x-ec-custom-error: 1
Content-Length: 0
```

## GET

* The GET method means retrieve whatever information (in the form of an entity) is identified by the Request-URI.
* The semantics of the GET method change to a "conditional GET" if the request message includes an:
	* If-Modified-Since
	* If-Unmodified-Since
	* If-Match
	* If-None-Match
	* If-Range
* A conditional GET method requests that the entity be transferred only under the circumstances described by the conditional header field(s).
* The semantics of the GET method change to a "partial GET" if the request message includes a Range header field.
* The response to a GET request is cacheable if and only if it meets the requirements for HTTP caching.

Ex. `GET /index.html`

## HEAD

* The HEAD method is identical to GET except that the server MUST NOT return a message-body in the response.

Ex. `HEAD /index.html`

## POST

* The POST method is used to request that the origin server accept the entity enclosed in the request.
* The actual function performed by the POST method is determined by the server and is usually dependent on the Request-URI.
* The action performed by the POST method might not result in a resource that can be identified by a URI.
	* 200 (OK)
	* or 204 (No content)
* If a resource has been created on the origin server, the response SHOULD be 201 (Created) and contain an entity which describes the status of the request and refers to the new resource, and a Location header.
* Responses to this method are not cacheable
	* unless the response includes appropriate Cache-Control or Expires header fields.
	* However, the 303 (See Other) response can be used to direct the user agent to retrieve a cacheable resource.

Ex.
```text
POST / HTTP/1.1
Host: foo.com
Content-Type: application/x-www-form-urlencoded
Content-Length: 13

say=Hi&to=Mom
```

## PUT

* The PUT method requests that the enclosed entity be stored under the supplied Request-URI.
* If the Request-URI refers to an already existing resource:
	* the enclosed entity SHOULD be considered as a modified version of the one residing on the origin server.
* If the Request-URI does not point to an existing resource , the origin server can create the resource with that URI.
	* If a new resource is created, the origin server MUST inform the user agent via the 201 (Created) response.
	* If an existing resource is modified, either the 200 (OK) or 204 (No Content) response codes SHOULD be sent to indicate successful completion of the request.
	* The recipient of the entity MUST NOT ignore any Content-\* (e.g. Content-Range) headers that it does not understand or implement and MUST return a 501 (Not Implemented) response. 
* Responses to this method are not cacheable.

* The fundamental difference between the POST and PUT requests is reflected in the different meaning of the Request-URI.
* In POST, the URI:
	* identifies the resource that will handle the enclosed entity.
* In PUT, the URI:
	* identifies the entity enclosed with the request.

## DELETE

* The DELETE method requests that the origin server delete the resource identified by the Request-URI.
* A successful response SHOULD be 200 (OK)
	* 202 (Accepted) if the action has not yet been enacted
	* 204 (No Content) if the action has been enacted but the response does not include an entity.
* Responses to this method are not cacheable.

## TRACE

* The TRACE method is used to invoke a remote, application-layer loop-back of the request message.
* A TRACE request MUST NOT include an entity.
* TRACE allows the client to see what is being received at the other end of the request chain and use that data for testing or diagnostic information.
* Responses to this method MUST NOT be cached.

## CONNECT

* Establishes a tunnel to the server identified by the target resource.
* Mostly a proxy server command
* Use if the client needs HTTPS via the proxy.

# Status Code Definitions

## Informational 1xx

* There are no required headers for this class of status code.
* servers MUST NOT send a 1xx response to an HTTP/1.0 client

### 100 Continue

* The initial part of a request has been received and has not yet been rejected by the server.
* The server intends to send a final response after the request has been fully received and acted upon.
* The client SHOULD continue with its request.
* The server MUST send a final response after the request has been completed.

### 101 Switching Protocols

* change in the application protocol being used on this connection.
* server will switch protocols to those defined by the response's Upgrade header field immediately after the empty line which terminates the 101 response.
* The protocol SHOULD be switched only when it is advantageous to do so. (HTTP/1.1 > HTTP/1.2)

## Successful 2xx

* indicates that the client's request was successfully received, understood, and accepted.

### 200 OK

* The request has succeeded.

### 201 Created

* The request has been fulfilled and resulted in a new resource being created.
* This is typically the response sent after a PUT request.
* The origin server MUST create the resource before returning the 201 status code.
* If the action cannot be carried out immediately, the server SHOULD respond with 202 (Accepted) response instead.

### 202 Accepted

* The request has been accepted for processing, but the processing has not been completed.
* The 202 response is intentionally non-committal.
* The entity returned with thisresponse SHOULD include an indication of the request's current status.

### 203 Non-Authoritative Information

* The request was successful but the enclosed payload has been modified from that of the origin server's 200 OK response by a transforming proxy.

### 204 No Content

* The server has fulfilled the request but does not need to return an entity-body.
* The 204 response MUST NOT include a message-body

### 205 Reset Content

* The server has fulfilled the request and the user agent SHOULD reset the document view which caused the request to be sent.
* The response MUST NOT include an entity.

### 206 Partial Content

* The server has fulfilled the partial GET request for the resource.
* The request MUST have included a Range header field indicating the desired range.

* The response MUST looks like:
```text
HTTP/1.1 206 Partial Content
Date: Wed, 15 Nov 1995 06:25:24 GMT
Last-Modified: Wed, 15 Nov 1995 04:58:08 GMT
Content-Range: bytes 21010-47021/47022
Content-Length: 26012
Content-Type: image/gif

... 26012 bytes of partial image data ...
```

## Redirection 3xx

This class of status code indicates that further action needs to be taken by the user agent in order to fulfill the request.

### 300 Multiple Choices

* The target resource has more than one representation, each with its own more specific identifier, and information about the alternatives is being provided so that the user (or user agent) can select a preferred representation by redirecting its request to one or more of those identifiers.
* the server desires that the user agent engage in reactive negotiation to select the most appropriate representation(s) for its needs.
* This response is cacheable.

### 301 Moved Permanently

* The requested resource has been assigned a new permanent URI and any future references to this resource SHOULD use one of the returned URIs.
* The new permanent URI SHOULD be given by the Location field in the response.

### 302 Found

* This response code means that URI of requested resource has been changed temporarily.
* New changes in the URI might be made in the future. Therefore, this same URI should be used by the client in future requests.

### 303 See Other

* The response to the request can be found under a different URI and SHOULD be retrieved using a GET method on that resource.
* MUST NOT be cached.

### 304 Not Modified

* This is used for caching purposes. It is telling to client that response has not been modified. So, client can continue to use same cached version of response.

### 305 Use Proxy

* This means requested response must be accessed by a proxy.

### 306 (Unused)

* This response code is no longer used, it is just reserved currently. It was used in a previous version of the HTTP 1.1 specification.

### 307 Temporary Redirect

* Server sent this response to directing client to get requested resource to another URI with same method that used prior request.
* This has the same semantic than the 302 Found HTTP response code, with the exception that the user agent must not change the HTTP method used: if a POST was used in the first request, a POST must be used in the second request.

## Client Error 4xx

* The 4xx class of status code is intended for cases in which the client seems to have erred.

### 400 Bad Request

The request could not be understood by the server due to malformed syntax.

### 401 Unauthorized

* The request requires user authentication.
* The response MUST include a WWW-Authenticate header field.
* This is similar to 403, but in this case, authentication is possible.

### 402 Payment Required

* This code is reserved for future use.

### 403 Forbidden

* Client does not have access rights to the content so server is rejecting to give proper response.

### 404 Not Found

* The server has not found anything matching the Request-URI.

### 405 Method Not Allowed

* The request method is known by the server but has been disabled and cannot be used.
* The two mandatory methods, GET and HEAD, must never be disabled and should not return this error code.
* The response MUST include an Allow header containing a list of valid methods for the requested resource.

### 406 Not Acceptable

* This response is sent when the web server, after performing server-driven content negotiation, doesn't find any content following the criteria given by the user agent.

### 407 Proxy Authentication Required

* This is similar to 401 but authentication is needed to be done by a proxy.

### 408 Request Timeout

* The client did not produce a request within the time that the server was prepared to wait.

### 409 Conflict

* This response would be sent when a request conflict with current state of server.

### 410 Gone

* This response would be sent when requested content has been deleted from server.

### 411 Length Required

* The server refuses to accept the request without a defined Content-Length.

### 412 Precondition Failed

* The client has indicated preconditions in its headers which the server does not meet.

### 413 Request Entity Too Large

* The server is refusing to process a request because the request entity is larger than the server is willing or able to process.

### 414 Request-URI Too Long

* The server is refusing to service the request because the Request-URI is longer than the server is willing to interpret.

### 415 Unsupported Media Type

* The media format of the requested data is not supported by the server, so the server is rejecting the request.

### 416 Requested Range Not Satisfiable

* The range specified by the Range header field in the request can't be fulfilled; it's possible that the range is outside the size of the target URI's data.

### 417 Expectation Failed

* This response code means the expectation indicated by the Expect request header field can't be met by the server.

## Server Error

* Server is aware that it has erred or is incapable of performing the request.

### 500 Internal Server Error

* The server encountered an unexpected condition which prevented it from fulfilling the request.

### 501 Not Implemented

* The server does not support the functionality required to fulfill the request.

### 502 Bad Gateway

* This error response means that the server, while working as a gateway to get a response needed to handle the request, got an invalid response.

### 503 Service Unavailable

* The server is not ready to handle the request. Common causes are a server that is down for maintenance or that is overloaded.

### 504 Gateway Timeout

* This error response is given when the server is acting as a gateway and cannot get a response in time.

### 505 HTTP Version Not Supported

The server does not support, or refuses to support, the HTTP protocol version that was used in the request message.

# Access Authentication

* HTTP provides several OPTIONAL challenge-response authentication defined in RFC 2617.

# Content Negociation

[HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Content_negotiation)

# Caching in HTTP

[HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Caching)

# Header Field Definitions

[HERE](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers)
