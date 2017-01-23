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
	* tunnel (a relay point between two connections without changing the messages; tunnels are used when the communication needs to pass through an intermediary (such as afirewall) even when the intermediary cannot understand the contents of the messages.)
* If not tunnel -> may employ an internal cache for handling requests.
	* Not all responses are usefully cacheable
	* Some requests may contain modifiers which place special requirements on cache behavior.
* HTTP communication usually takes place over TCP/IP connections
	* can be Implemented on top of any other protocol on the Internet as long as the transport is reliable. (a.k.a not UDP)
* The default port is TCP 80.
* A connection may be used for one or more request/response exchanges.

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
* Major and minor numbers MUST be treated as separate integers and that each MAY be incremented higher than a single digit.
* Leading zeros MUST be ignored by recipients and MUST NOT be sent.
* The HTTP version of an application is the highest HTTP version for which the application is at least conditionally compliant.
* A proxy/gateway MUST NOT send a message with a version indicator which is greater than its actual version.
	* If a higher version request is received, the proxy/gateway MUST:
		* downgrade the request version
		* or respond with an error
		* or switch to tunnel behavior.

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

### HTTP URL

* `http_URL = "http:" "//" host [ ":" port ] [ abs_path [ "?" query ]]`
* If the port is empty or not given, port 80 is assumed
* The use of IP addresses in URLs SHOULD be avoided whenever possible.
* If the `abs_path` is not present in the URL, it MUST be given as "/" when used as a Request-URI for a resource.

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
* HTTP-date is case sensitive and MUST NOT include additional LWS beyond that specifically included as SP in the grammar.

**See RFC 2616 section 3.3.1 for BNF lovers**

## Charset

* HTTP character sets are identified by case-insensitive tokens.
* The complete set of tokens is defined by the IANA Character Set registery
* `charset = token`

## Content Codings

* `content-encoding = token`
* All content-coding values are case-insensitive
* HTTP/1.1 uses content-encoding values in header fields:
	* `Accept-Encoding`
	* `Content-Encoding`
* The Internet Assigned Numbers Authority (IANA) acts as a registry for content-coding value tokens.
* Initially, the regisrty contains the following tokens:
	* gzip (An encoding format produced by the file compression program "gzip" (GNU zip) as described in RFC 1952.)
	* compress (The encoding format produced by the common UNIX file compression program "compress". For compatibility with previous implementations of HTTP, applications SHOULD consider "x-gzip" and "x-compress" to be equivalent to "gzip" and "compress" respectively.)
	* deflate (The "zlib" format defined in RFC 1950 in combination with the "deflate" compression mechanism described in RFC 1951.)
	* identity (The default (identity) encoding; the use of no transformation whatsoever. This content-coding is used only in the Accept-Encoding header, and SHOULD NOT be used in the Content-Encoding header.)

## Transfert Codings

* Indicate an encoding transformation that has been, can be, or may need to be applied to an entity-body in order to ensure "safe transport" through the network.

**See RFC 2616 section 3.6 for BNF**

* This differs from a content coding in that the transfer-coding is a property of the message, not of the original entity.
* All transfer-coding values are case-insensitive.
* HTTP/1.1 uses transfer-coding values in
	* the TE header field
	* the Transfer-Encoding header field
* The set of transfer-codings MUST include "chunked", unless the message is terminated by closing the connection. 
	* It MUST be the last transfer-coding applied to the message-body.
	* The "chunked" transfer-coding MUST NOT be applied more than once to a message-body.
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

### Chunked Transfert Coding

* The chunked encoding modifies the body of a message in order to transfer it as a series of chunks.
	* each with
		* its own size indicator
		* followed by an OPTIONAL trailer containing entity-header fields.

**See RFC 2616 section 3.6.1 for BNF**

* The chunked encoding is ended by any chunk whose size is zero
	* followed by the trailer, which is terminated by an empty line.
* The Trailer header field can be used to indicate which header fields are included in a trailer.
* A server using chunked transfer-coding in a response MUST NOT use the trailer for any header fields unless at least one of the following is true:
	* the request included a TE header field that indicates "trailers" is acceptable in the transfer-coding of the  response.
	* the server is willing to accept the possibility that the trailer fields might be silently discarded along the path to the client.
* All HTTP/1.1 applications MUST:
	* be able to receive and decode the "chunked" transfer-coding
	* ignore chunk-extension extensions they do not understand.

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

### Canonicalization and text defaults

* Internet media types are registered with a canonical form.
* An entity-body transferred via HTTP messages MUST be represented in the appropriate canonical form prior to its transmission
	* except for "text" types.
* Media subtypes of the "text" type use CRLF as the text line break.
	* HTTP applications MUST accept CRLF, bare CR, and bare LF as being representative of a line break in text media received.
	* Applies only to text media in the entity-body
		* a bare CR or LF MUST NOT be substituted for CRLF within any of the HTTP control structures (such as header fields and multipart boundaries).
* If an entity-body is encoded with a content-coding, the underlying data MUST be in a form defined above prior to being encoded. #logic
* When no explicit charset parameter is provided by the sender, media subtypes of the "text" type are defined to have a default charset value of "ISO-8859-1" when received.

### Multipart Types

* "multipart" types: encapsulations of one or more entities within a single message-body.
* All multipart types:
	* share a common syntax, as defined in section 5.1.1 of RFC 2046
	* MUST include a boundary parameter as part of the media type value
* The message body is itself a protocol element and MUST therefore use only CRLF to represent line breaks between body-parts.
* The epilogue of any multipart message MUST be empty.
* HTTP applications MUST NOT transmit the epilogue.
* HTTP treats a multipart message-body no differently than any other media type: strictly as payload.
	* The one exception is the "multipart/byteranges" type when it appears in a 206 (Partial Content) response, which will be interpreted by some HTTP caching mechanisms.
	* In all other cases, an HTTP user agent SHOULD follow the same or similar behavior as a MIME user agent would upon receipt of a multipart type.
* An HTTP user agent SHOULD follow the same or similar behavior as a MIME user agent would upon receipt of a multipart type.

## Product Tokens

* Used to allow communicating applications to identify themselves by software name and version.
* Most fields using product tokens also allow sub-products which form a significant part of the application to be listed, separated by white space.
* By convention, the products are listed in order of their significance for identifying the application.

**See RFC 2616 section 3.8 for BNF**

* Ex: `Server: Apache/0.8.4`, `User-Agent: CERN-LineMode/2.15 libwww/2.17b3`
* Product tokens SHOULD be short and to the point.
* They MUST NOT be used for advertising or other non-essential information.
* Although any token character MAY appear in a product-version, this token SHOULD only be used for a version identifier.

## Quality Values

* HTTP content negotiation uses short "floating point" numbers to indicate the relative importance ("weight") of various negotiable parameters. 
* A weight is normalized to a real number in the range 0 through 1, where 0 is the minimum and 1 the maximum value.
* If a parameter has a quality value of 0, then content with this parameter is 'not acceptable' for the client.
* HTTP/1.1 applications MUST NOT generate more than three digits after the decimal point.

**See RFC 2616 section 3.9 for BNF**

## Language Tags

* A language tag identifies a natural language spoken, written, or otherwise conveyed by human beings for communication of information to other human beings.
* HTTP uses language tags with:
	* `Accept-Language`
	* `Content-Language`
* The syntax and registry of HTTP language tags is the same as that defined by RFC 1766.
* White space is not allowed within the tag
* All tags are case-insensitive.
* The name space of language tags is administered by the IANA.
* A language tag is composed of 1 or more parts.

**See RFC 2616 section 3.10 for BNF**

* Ex. `en`, `en-US`
* where any two-letter primary-tag is an ISO-639 language abbreviation and any two-letter initial subtag is an ISO-3166 country code.

## Entity Tags

* Entity tags are used for comparing two or more entities from the same requested resource.
* HTTP/1.1 uses entity tags in the following header fields:
	* ETag
	* If-Match
	* If-None-Match
	* If-Range

**See RFC 2616 section 3.11 for BNF**

* A "strong entity tag" MAY be shared by two entities of a resource only if they are equivalent by octet equality.
* A "weak entity tag," indicated by the "W/" prefix, MAY be shared by two entities of a resource only if:
	* the entities are equivalent
	* could be substituted for each other with no significant change in semantics
* A weak entity tag can only be used for weak comparison.
* An entity tag MUST be unique across all versions of all entities associated with a particular resource.

## Range Units

* Client can request that only part (a range of) the response entity be included within the response.
* Client uses range units in the header fields:
	* `Range`
	* `Content-Range`

**See RFC 2616 section 3.12 for BNF**

* The only range unit defined is "bytes".
* Implementations MAY ignore ranges specified using other units.

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

## Message Headers

* HTTP header fields can be:
	* general-header
	* request-header
	* response-header
	* entity-header
* Each header field consists of a name followed by a colon (":") and the field value.
* Field names are case-insensitive.
* The field value MAY be preceded by any amount of LWS, though a single SP is preferred.
* Header fields can be extended over multiple lines by preceding each extra line with at least one SP or HT.

**See RFC 2616 section 4.2 for BNF**

* It is "good practice" to send:
	* general-header fields first
	* followed by request-header or response-eader fields
	* ending with the entity-header fields.
* Multiple message-header fields with the same field-name MAY be present in a message if and only if the entire field-value for that header field is defined as a comma-separated list [i.e., #(values)].
* It MUST be possible to combine the multiple header fields into one "field-name: field-value" pair, without changing the semantics of the message, by appending each subsequent field-value to the first, each separated by a comma.

## Message Body

* The message-body (if any) of an HTTP message is used to carry the entity-body associated with the request or response.
* The message-body differs from the entity-body only when a transfer-coding has been applied.
* Transfer-Encoding MUST be used to indicate any transfer-codings applied by an application.
* The presence of a message-body in a request is signaled by the inclusion of one of those header fields:
	* `Content-Length`
	* `Transfer-Encoding`
* A message-body MUST NOT be included in a request if the specification of the request method does not allow sending an entity-body in requests.
* A server SHOULD read and forward a message-body on any request
	* if the request method does not include defined semantics for an entity-body, then the message-body SHOULD be ignored when handling the request.
* For response messages, whether or not a message-body is included with a message is dependent on both the request method and the response status code.
	* All responses to the HEAD request method MUST NOT include a message-body
	* All 1xx (informational), 204 (no content), and 304 (not modified) responses MUST NOT include a message-body.
	* All other responses do include a message-body, although it MAY be of zero length.

## Message Length

* The transfer-length of a message is the length of the message-body as it appears in the message.
	* that is, after any transfer-codings have been applied.

* When message-body: the transfer-length of that body is determined by one of the following:
	* Any response message which "MUST NOT" include a message-body (such as the 1xx, 204, and 304 responses and any response to a HEAD request) is always terminated by the first empty line after the header fields.
	* If a `Transfer-Encoding` header field is present and has any value other than "identity":
		* then the transfer-length is defined by use of the "chunked" transfer-coding (unless the message is terminated by closing the connection)
	* If a `Content-Length` header field is present, its decimal value in OCTETs represents both the entity-length and the transfer-length. The `Content-Length` header field MUST NOT be sent if these two lengths are different. If a message is received with both a `Transfer-Encoding` header field and a `Content-Length` header field, the latter MUST be ignored.
	* If the message uses the media type "multipart/byteranges", and the transfer-length is not otherwise specified, then this self-elimiting media type defines the transfer-length. This media type MUST NOT be used unless the sender knows that the recipient can parse it. The presence in a request of a Range header with ultiple byte-range specifiers from a 1.1 client implies that the client can parse multipart/byteranges responses.
	* By the server closing the connection. (Closing the connection cannot be used to indicate the end of a request body, since that would leave no possibility for the server to send back a response.)

* If a request contains a message-body and a `Content-Length` is not given, the server SHOULD respond:
	* with 400 (bad request) if it cannot determine the length of the message or
	* with 411 (length required) if it wishes to insist on receiving a valid `Content-Length`.
* All HTTP/1.1 applications that receive entities MUST accept the "chunked" transfer-coding thus allowing this mechanism to be used for messages when the message length cannot be determined in advance.
* Messages MUST NOT include both a `Content-Length` header field and a non-identity transfer-coding.
	* If the message does include a non-identity transfer-coding, the `Content-Length` MUST be ignored.
* When a `Content-Length` is given in a message where a message-body is allowed, its field value MUST exactly match the number of OCTETs in the message-body.
	* HTTP/1.1 user agents MUST notify the user when an invalid length is received and detected.

## General Header Fields

**See RFC 2616 section 4.5 for BNF**

# Request

**See RFC 2616 section 5 for BNF**

## Request-Line

* The Request-Line:
	* begins with a method token. (Ex. `POST`)
	* followed by the Request-URI
	* and the protocol version
	* ending with a CRLF.
* `Request-Line   = Method SP Request-URI SP HTTP-Version CRLF`

### Method

* The method is case-sensitive.
* `OPTIONS`, `GET`, `HEAD`, `POST`, `PUT`, `DELETE`, `TRACE`, `CONNECT`
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

## The Resource Identified by a Request

* The exact resource identified by an Internet request is determined by examining:
	* the Request-URI
	* the Host header field
* An origin server that does not allow resources to differ by the requested host MAY ignore the Host header field value.
* An origin server that does differentiate resources based on the host requested (virtual hosts) MUST use the following rules:
	* If Request-URI is an absoluteURI -> Host header field value in the request MUST be ignored.
	* If the Request-URI is not an absoluteURI and request includes a Host header field -> the host is determined by the Host header field value.
	* If the host as determined by rule 1 or 2 is not a valid host on the server, the response MUST be a 400 (Bad Request) error message.

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
	* With the exception that an unrecognized response MUST NOT be cached.

## Response Header Fields

* Allow the server to pass additional information about the response which cannot be placed in the Status-Line.

**See RFC 2616 section 6.2 for BNF**

* Unrecognized header fields are treated as entity-header fields.

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

## Message Transmission Requirements

### Persistent Connections and Flow Control

* Servers SHOULD maintain persistent connections and use TCP's flow control mechanisms to resolve temporary overloads, rather than terminating connections with the expectation that clients will retry.

### Use of the 100 (Continue) Status

* Allow a client that is sending a request message with a request body to determine if the origin server is willing to accept the request (based on the request headers) before the client sends the request body.
* Upon receiving a request which includes an Expect request-header field with the "100-continue" expectation, an origin server MUST either respond with:
	* 100 (Continue) status and continue to read from the input stream
	* or respond with a final status code.
* The origin server MUST NOT wait for the request body before sending the 100 (Continue) response.
* If it responds with a final status code:
	* it MAY close the transport connection
	* or it MAY continue to read and discard the rest of the request.
	* It MUST NOT perform the requested method if it returns a final status code.
* An origin server SHOULD NOT send a 100 (Continue) response if the request message does not include an Expect request-header field with the "100-continue" expectation
* An origin server MUST NOT send a 100 (Continue) response if such a request comes from an HTTP/1.0 (or earlier) client.
* a server MAY send a 100 (Continue)  status in response to an HTTP/1.1 PUT or POST request that doesnot include an Expect request-header field with the "100-continue" expectation.
* An origin server MAY omit a 100 (Continue) response if it has already received some or all of the request body for the corresponding request.
* An origin server that sends a 100 (Continue) response MUST ultimately send a final status code, once the request body is received and processed, unless it terminates the transport connection prematurely.

# Method Definitions

## Safe and Idempotent Methods

### Safe Methods

* the convention has been established that the GET and HEAD methods SHOULD NOT have the significance of taking an action other than retrieval.
* These methods ought to be considered "safe".

## OPTION

* This method allows the client to determine:
	* options and/or requirements associated with a resource
	* capabilities of a server
	* initiating a resource retrieval
* Responses to this method are not cacheable.
* If the OPTIONS request includes an entity-body (as indicated by the presence of Content-Length or Transfer-Encoding), then the media type MUST be indicated by a Content-Type field.
* If the Request-URI is an asterisk ("\*"), the OPTIONS request is intended to apply to the server in general
* It does nothing beyond allowing the client to test the capabilities of the server.
* If the Request-URI is not an asterisk, the OPTIONS request applies only to the options that are available when communicating with that resource.
* A 200 response SHOULD include any header fields that indicate optional features implemented by the server and applicable to that resource (e.g., Allow)
* The response body, if any, SHOULD also include information about the communication options. The format for such a body is not defined.
* If no response body is included, the response MUST include a Content-Length field with a field-value of "0".

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

## HEAD

* The HEAD method is identical to GET except that the server MUST NOT return a message-body in the response.

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
* In GET, the URI:
	* identifies the entity enclosed with the request.
	* server MUST NOT attempt to apply the request to some other resource.
	* If the server desires that the request be applied to a different URI, it MUST send a 301 (Moved Permanently) response.
* A single resource MAY be identified by many different URIs.

## DELETE

* The DELETE method requests that the origin server delete the resource identified by the Request-URI.
* A successful response SHOULD be 200 (OK)
	* 202 (Accepted) if the action has not yet been enacted
	* 204 (No Content) if the action has been enacted but the response does not include an entity.
* Responses to this method are not cacheable.

## TRACE

* The TRACE method is used to invoke a remote, application-layer loop-back of the request message.
* A TRACE request MUST NOT include an entity..
* TRACE allows the client to see what is being received at the other end of the request chain and use that data for testing or diagnostic information.
* The value of the Via header field is of particular interest, since it acts as a trace of the request chain.
* If the request is valid, the response SHOULD contain the entire request message in the entity-body, with a Content-Type of "message/http".
* Responses to this method MUST NOT be cached.

## CONNECT

* A proxy server command
* Use if the client needs HTTPS via the proxy.

# Status Code Definitions

## Informational 1xx

* consisting only of the Status-Line and optional headers and is terminated by an empty line.
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
* The newly created resource can be referenced by the URI(s) returned in the entity of the response, with the most specific URI for the resource given by a Location header field.
* The response SHOULD include an entity containing a list of resource characteristics and location(s) from which the user or user agent can choose the one most appropriate.
* The origin server MUST create the resource before returning the 201 status code.
* If the action cannot be carried out immediately, the server SHOULD respond with 202 (Accepted) response instead.
* A 201 response MAY contain an ETag response header field indicating the current value of the entity tag for the requested variant just created.

### 202 Accepted

* The request has been accepted for processing, but the processing has not been completed.
* The 202 response is intentionally non-committal.
* The entity returned with thisresponse SHOULD include an indication of the request's current status.

### 203 Non-Authoritative Information

* The request was successful but the enclosed payload has been modified from that of the origin server's 200 OK response by a transforming proxy.

### 204 No Content

* The server has fulfilled the request but does not need to return an entity-body.
* The 204 response MUST NOT include a message-body
* always terminated by the first empty line after the header fields.

### 205 Reset Content

* The server has fulfilled the request and the user agent SHOULD reset the document view which caused the request to be sent.
* The response MUST NOT include an entity.

### 206 Partial Content

* The server has fulfilled the partial GET request for the resource.
* The request MUST have included a Range header field indicating the desired range.
* MAY have included an If-Range header field  to make the request conditional.

* The response MUST include the following header fields:
	* Either a Content-Range header field indicating the range included with this response , or a multipart/byteranges Content-Type including Content-Range fields for each part. If a Content-Length header field is present in the response, its value MUST match the actual number of OCTETs transmitted in the message-body.
	* Date
	* ETag and/or Content-Location, if the header would have been sent in a 200 response to the same request
	* Expires, Cache-Control, and/or Vary, if the field-value might differ from that sent in any previous response for the same variant.

* Ex.
```text
HTTP/1.1 206 Partial Content
Date: Wed, 15 Nov 1995 06:25:24 GMT
Last-Modified: Wed, 15 Nov 1995 04:58:08 GMT
Content-Range: bytes 21010-47021/47022
Content-Length: 26012
Content-Type: image/gif

... 26012 bytes of partial image data ...
```

* If the 206 response is the result of an If-Range request that used a strong cache validator, the response SHOULD NOT include other entity-headers.
* If the response is the result of an If-Range request that used a weak validator, the response MUST NOT include other entity-headers.
* Otherwise, the response MUST include all of the entity-headers that would have been returned with a 200 (OK) response to the same request.

## Redirection 3xx

This class of status code indicates that further action needs to be taken by the user agent in order to fulfill the request.
