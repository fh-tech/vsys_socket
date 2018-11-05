## Protocol

### Communication Protocol

#### LOGIN
* see /doc/exercise_description.pdf
* if 3 attempts to login failed the client`s ip is saved in a table in the sqlite database with the current UNIX-timestamp

#### SEND
* see /doc/exercise_description.pdf

#### LIST
* see /doc/exercise_description.pdf
##### Response
* the server fetches all mails for the username of the Clientconnection from the database
* the server builds a vector of MailDetail objects which hold
    * subject
    * id in database
* he then sends them to the client
    * starts with LIST
    * then for every message:
        * id and subject separated by a space
        * \n
    * then a "." to terminate the message

* the client then parses the ServerResponse and saves the resulting MailDetail-Collection as his inbox

#### READ
* see /doc/exercise_description.pdf

##### Response
* the server fetches the mail with the specified id from the database
* if no mail matches the ServerResponse Error is returned
* if a mail-entry is found the server builds a Mail_out object
* he then sends it to the server like this:
    * MAIL
    * subject
    * from
    * to
    * payload
    * "."
* the client then parses the ServerResponse and prints it to the user

#### DEL
* see /doc/exercise_description.pdf

#### QUIT