#include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
using namespace std;

struct MemoryStruct
{
    char *memory;
    size_t size;
};

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = (char *)realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr)
    {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int main(int argc, char *argv[ ])
{
    /*
        1- test sendHttp   function
        2- test getStorage function
        3- test triggerLED function
    */
    int switcher;
    if (argc > 1)
    {
        switcher = atoi(argv[1]);
    }    
    else
    {
        switcher = 0;
    }

    cout << "Starting test ..." << endl;

    // switchs between different tests
    switch (switcher)
    {
    // -------------------------------------------------------------------------------------------
    // FUNÇÂO sendHTTP
    case 1:
        {
            cout << "Function sendHttp" << endl;
            cout << "Should return a JSON with the POST form data and save the file sent";
            cout << " in the path specified in the server" << endl;

            cout << endl;

            cout << "Specify FULL path to the file you want to send: (ex: /home/...../src/test_file.txt)" << endl;

            static string send_file;
            cin >> send_file;

            // static keywork makes varibles local to this scope
            static CURL *curl;
            static CURLcode response;

            static bool status = false;

            string datetime = "agora";
            double latitude = 1.0;
            double longitude = 2.0;
            double speed = 3.0;
            double trackAngle = 4.0;
            double temperature = 5.0;

            string lat = to_string(latitude);
            string lon = to_string(longitude);
            string spd = to_string(speed);
            string tckA = to_string(trackAngle);
            string temp = to_string(temperature);

            // get a curl handle
            curl = curl_easy_init();
            if (curl)
            {
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
                // set URL to recieve requisition
                curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5000/test_sendHttp"); // http://localhost:5555 https://postman-echo.com/post

                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

                curl_easy_setopt(curl, CURLOPT_USERAGENT, "retina-libcurl-agent/1.0");

                curl_mime *mime;
                curl_mimepart *part;
                mime = curl_mime_init(curl);

                part = curl_mime_addpart(mime);
                curl_mime_name(part, "Datetime");
                curl_mime_data(part, datetime.c_str(), CURL_ZERO_TERMINATED);

                part = curl_mime_addpart(mime);
                curl_mime_name(part, "Latitude");
                curl_mime_data(part, lat.c_str(), CURL_ZERO_TERMINATED);

                part = curl_mime_addpart(mime);
                curl_mime_name(part, "Longitude");
                curl_mime_data(part, lon.c_str(), CURL_ZERO_TERMINATED);

                part = curl_mime_addpart(mime);
                curl_mime_name(part, "Speed");
                curl_mime_data(part, spd.c_str(), CURL_ZERO_TERMINATED);

                part = curl_mime_addpart(mime);
                curl_mime_name(part, "TrackAngle");
                curl_mime_data(part, tckA.c_str(), CURL_ZERO_TERMINATED);

                part = curl_mime_addpart(mime);
                curl_mime_name(part, "Temperature");
                curl_mime_data(part, temp.c_str(), CURL_ZERO_TERMINATED);

                part = curl_mime_addpart(mime);
                curl_mime_name(part, "Image");
                curl_mime_filedata(part, send_file.c_str());
                curl_mime_filename(part, "Image");

                curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

                response = curl_easy_perform(curl);
                curl_mime_free(mime);

                /* Check for errors */
                if (response != CURLE_OK)
                {
                    status = false;
                }
                else
                {
                    status = 2;
                }
            }

            // curl cleanup
            curl_easy_cleanup(curl);

            cout << "\n status: " << status << endl;
            break;
        }
    

    // -------------------------------------------------------------------------------------------
    // FUNÇÂO getStorage
    case 2:
        {
            cout << "Function getStorage" << endl;
            cout << "Should return the status returned in the server response" << endl;
            
            // static keywork makes varibles local to this scope
            static CURL *curl;
            static CURLcode response;
            static struct MemoryStruct chunk;
            static bool status = true;
            static char full_storage;

            chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
            chunk.size = 0;    /* no data at this point */

            // get a curl handle
            curl = curl_easy_init();
            if (curl){
                // define request method as POST
                curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
                // set URL to recieve request
                curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5000/test_getStorage");

                /* send all data to this function  */
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

                /* we pass our 'chunk' struct to the callback function */
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

                curl_easy_setopt(curl, CURLOPT_USERAGENT, "retina-libcurl-agent/1.0");

                response = curl_easy_perform(curl);

                /* check for errors */
                if(response != CURLE_OK) {
                    // curl error happened
                }
                else {
                    /*
                    * Now, our chunk.memory points to a memory block that is chunk.size
                    * bytes big and contains the remote file.
                    *
                    * Do something nice with it!
                    */
                    full_storage = *chunk.memory;
                    
                    if (full_storage == '0')
                            status = false;
                }
            }
            // curl cleanup
            std::cout << "Status: " << status << std::endl;
            curl_easy_cleanup(curl);

            free(chunk.memory);
            break;
        }
    
    // -------------------------------------------------------------------------------------------
    // FUNÇÂO triggerLED
    case 3:
        {        
            cout << "Function triggerLED" << endl;
            cout << "Should return a JSON with the POST form data" << endl;
            
            // static keywork makes varibles local to this scope
            static int error_code = 800;
            static bool status = true;
            static string send_string = "error="+to_string(error_code);

            static CURL *curl;
            static CURLcode response;

            // get a curl handle
            curl = curl_easy_init();
            if(curl) {
                    // define request method as POST
                    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
                        // set URL to recieve request
                    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5000/test_triggerLED");

                    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

                    // set content-type header
                    struct curl_slist *headers = NULL;
                    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
                    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

                    // set post fields
                    const char *data = send_string.c_str();
                    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

                    // perform request and get return code
                    response = curl_easy_perform(curl);
                    if(response != CURLE_OK) {
                        status = false;
                    }
                    else {
                        status = 2;
                    }
            }
            // curl cleanup
            curl_easy_cleanup(curl);

            cout << "status: " << status << endl;
            break;
        }

    default:
        cout << "provide valid command line arguments" << endl;
        cout << "1 -> test sendHttp   function" << endl;
        cout << "2 -> test getStorage function" << endl;
        cout << "3 -> test triggerLED function" << endl;
        break;
    }

    cout << "Test finished! " << endl;

    return 0;
}