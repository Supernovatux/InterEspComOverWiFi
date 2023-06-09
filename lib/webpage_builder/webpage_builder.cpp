#include "webpage_builder.hpp"
static const char* Header = "<!DOCTYPE html>\n"
                            "<html lang=\"en\">\n"
                            "\n"
                            "<head>\n"
                            "  \n"
                            "  <meta charset=\"UTF-8\" />\n"
                            "  <meta name=\"viewport\" content=\"width=device-width, "
                            "initial-scale=1.0\" />\n"
                            "  <title>Browser</title>\n"
                            "  <style>\n"
                            "      body {\n"
                            "      margin: 20px;\n"
                            "    }\n"
                            "\t table,th,td{\n"
                            "\n"
                            "        text-align:center;\n"
                            "        border-radius: 10px;\n"
                            "        border: 2px solid;\n"
                            "        padding: 2px; \n"
                            "        width: 2px;\n"
                            "        height: 1px;\n"
                            "    \tbackground-colour:#71deec;\n"
                            "    }  \t\n"
                            "\n"
                            "    th{\n"
                            "        background-color: #1ecbe1;\n"
                            "        color: #052529;\n"
                            "    }\n"
                            "  </style>\n"
                            "</head>\n"
                            "\n"
                            "<body>\n"
                            " <table style=\"width:100%\"><tr>";
void build_webpage(String& webpage, devices* newdev)
{
    webpage = Header;
    for (int i = 0; i < 2; i++) {
        webpage += "<th>";
        webpage += String("<p> Device ") + String(i) + String("</p></th>");
    }
    webpage += "</tr>";

    for (int j = 0; j < 5; j++) {
        webpage += "<tr>";
        for (int i = 0; i < 2; i++) {
            webpage += "<td>";
            if (newdev->nodes[i].sensors[j].status) {
                webpage += String("<p> LED: ON</p><a class=\"button button-off\" "
                                  "href=\"/ledoff?message=")
                    + String(i) + String(",") + String(j) + String("\">OFF</a>\n");
            } else {
                webpage += String("<p> LED: OFF</p><a class=\"button button-on\" "
                                  "href=\"/ledon?message=")
                    + String(i) + String(",") + String(j) + String("\">ON</a>\n");
            }
            webpage += "</td>";
        }
    }
    webpage += "</tr></table>";
}