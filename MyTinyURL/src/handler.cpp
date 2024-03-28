#include <string>
#include <vector>
#include <sstream>

#include "include/handler.h"
#include "src/database.cpp"
#include "src/Base62Generator.cpp"
#include "src/dataHandler.cpp"

using namespace std;

extern database db;

handler::handler()
{

    //ctor

}
handler::handler(utility::string_t url):m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&handler::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&handler::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&handler::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&handler::handle_delete, this, std::placeholders::_1));
}
handler::~handler()
{

    //dtor

}

void handler::handle_error(pplx::task<void>& t)
{
    try
    {
        t.get();
    }
    catch(...)
    {
        // Ignore the error, Log it if a logger is available
    }
}


//
// Get Request 
//
void handler::handle_get(http_request message)
{   
    // Set IP and port address
    utility::string_t address = U("127.0.0.1:");
    utility::string_t port = U("34568");

    // Extract the code from the URI
    utility::string_t base62code = message.relative_uri().path();
    
    // Generate full mapped address
    utility::string_t requestBody = address + port + base62code;

    // Build to the original url from database
    utility::string_t originalURL = db.getValue(requestBody);
    // Build redirect url for response
    utility::string_t redirectUrl = U("http://" + originalURL);//U("http://www.example.com");
    // Create the response
    http_response response(status_codes::Found);
    response.headers().add(U("Location"), redirectUrl);
    // Send the response to the server
    message.reply(response);
    //message.reply(status_codes::Found, U(db.getValue(requestBody)));

    // Extract request body
    requestBody = message.extract_string().get();

    // Print info in cmd line
    if(db.containsKey(requestBody)) {
        ucout << "Request Body: " << requestBody << endl;
        ucout << "Found original URL: " << db.getValue(requestBody) << endl;
    } 
    
    // Send reply to the server
    message.reply(status_codes::OK,message.to_string());
    
    return;
};

//
// A POST request
//
void handler::handle_post(http_request message)
{
    // Set IP and port address
    utility::string_t address = U("127.0.0.1:");
    utility::string_t port = U("34568");

    // Extract request body
    utility::string_t requestBody = message.extract_string().get(); 
    ucout << "Request Body: " << requestBody << endl;
    utility::string_t longURL = requestBody;

    // Generate the code for short URL
    Base62Generator base62Generator;
    utility::string_t base62code = base62Generator.generate();
    
    // Genereate new base 62 code
    cout << "Generated base62code: " << base62code << endl;
    // Build short URL
    string shortURL = address + port + "/" + base62code;
    // Print short URL in cmd line
    cout << "Short URL: " << shortURL << endl;

    // Update database
    db.insert(shortURL, longURL);

    // Open datafile
    dataHandler file("/home/nicolaedanieldogaru/Documents/Restweb-master/data/data.txt");

    // Write info to datafile
    if (file.writeToTextFile(shortURL + " " + longURL)) {
        cout << "Data written to file successfully." << endl;
    }

    //Send reply to the server
    message.reply(status_codes::OK,message.to_string());
    
    return ;
};

//
// A DELETE request
//
void handler::handle_delete(http_request message)
{
    cout << "DEL" << endl;

    ucout <<  message.to_string() << endl;

    string rep = U("WRITE YOUR OWN DELETE OPERATION");
    message.reply(status_codes::OK,rep);
     
    return;
};


//
// A PUT request 
//
void handler::handle_put(http_request message)
{
    cout << "PUT" << endl;

    ucout <<  message.to_string() << endl;

    string rep = U("WRITE YOUR OWN PUT OPERATION");
    message.reply(status_codes::OK,rep);

    return;
};
