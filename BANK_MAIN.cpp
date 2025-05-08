#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


// Read from a file
vector<vector<string>> readFile(const string &filename) {
    vector<vector<string>> data;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> row;
        string cell;
        while (getline(ss, cell, ','))
            row.push_back(cell);
        data.push_back(row);
    }
    return data;
}

// Escape special characters in CSV
string escapeCSV(const string& field) {
    string escaped = field;
    bool needsQuotes = escaped.find(',') != string::npos ||
                       escaped.find('"') != string::npos ||
                       escaped.find('\n') != string::npos;

    if (needsQuotes) {
        size_t pos = 0;
        while ((pos = escaped.find('"', pos)) != string::npos) {
            escaped.insert(pos, "\""); // Escape quotes by doubling them
            pos += 2;
        }
        escaped = "\"" + escaped + "\"";
    }

    return escaped;
}

//Write to a file
void writeFile(const string& filename, const vector<string>& row) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << " Could not open file: " << filename << endl;
        return;
    }

    for (size_t i = 0; i < row.size(); ++i) {
        file << escapeCSV(row[i]);
        if (i < row.size() - 1) file << ",";
    }
    file << "\n";
}

//Update a file
void updateFile(const string& filename, const vector<vector<string>>& data) {

    ofstream outFile(filename);
    if (!outFile) {
        cerr << " Could not open file: " << filename << endl;
        return;
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            outFile << escapeCSV(row[i]);
            if (i < row.size() - 1) outFile << ",";
        }
        outFile << "\n";
    }

    outFile.close();
}

//sending To client
void sendPrompt(int sock, const string &msg) {
    send(sock, msg.c_str(), msg.length(), 0);
    cout << "[SEND] " << msg << endl;
}

//Receiving from Client
string receiveInput(int sock) {
    char buffer[4096];
    int bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);

    if (bytesReceived <= 0) {
        cout << "[RECV] Connection closed or no data.\n";
        return "";
    }

    buffer[bytesReceived] = '\0';
    cout << "[RECV] " << buffer << endl;
    return string(buffer);
}

//Check Valid Phone number or not
bool validPhone(string phno)
{
   if(phno.length()!=10||(!all_of(str.begin(), str.end(),isdigit)))
    return false;
    else
        return true;
}


//----------Handle Client----------------
void handleClient(string accno,int sock)
{
    while(true)
    {
    stringstream ss;
    ss<<";
    ss<<"\n|----------------------------------------------------|";
    ss<<"\n|----------------------------------------------------|";
    ss<<"\n|               STATE BANK OF INDIA                  |";
    ss<<"\n|----------------------------------------------------|";
    ss<<"\n|----------------------------------------------------|";
  ss<<"\n|1.ACCOUNT DETAILS           2. SEND MONEY           |";
  ss<<"\n|3.CHECK ACCOUNT BALANCE     4. TRANSACTION HISTORY  |";
    ss<<"\n|----------------------------------------------------|";
    ss<<"\n               WHAT SERVICE YOU WANT? ";
    sendPrompt(sock,ss);
        int choice=receiveInput(sock);
        if(choice==1)
            accountDetails(sock,accNo);
        else if(choice==2)
            sendmoney(sock);
        else if(choice==3)
            checkBalance(sock);
        else if()
            transactionHistory(sock);
    }
}

class Entry
{
private:
    string Aadhar;

};

//---------Entrance Function----------------
void Entry::entrance(int sock)
{
    stringstream ss;
    ss<<"\n|----------------------------------------------------|";
    ss<<"\n|----------------------------------------------------|";
    ss<<"\n|           WELCOME TO STATE BANK OF INDIA           |";
    ss<<"\n|----------------------------------------------------|";
    ss<<"\n|----------------------------------------------------|";
    ss<<"\nWe Welcome You All in this Automated Banking Service";
    SS<<"\n              TO AVAIL THE FEATURES \n";
    SS<<"       LINK YOUR PHONE NUMBER WITH THE BANK ACCOUNT ";
    ss<<"\n--------------------------------------------------";
    ss<<"\nTO EXIT PRESS: CTRL+C";
    ss<<"\n--------------------------------------------------";
    sendPrompt(sock,ss);
    while(true)
    {
        sendPrompt(sock,"\n\n Enter Your LINKED MOBILE NUMBER:");
        string Phno=receiveInput(sock);
        if(!validPhoneNo(phno))
        {
            sendPrompt("Not a Valid Phone Number. RE_ENTER....")
            continue;
        }
    }
    sendPrompt(sock,"\n\n Enter Your LINKED MOBILE NUMBER:");
    string Phno=receiveInput(sock);
    if(validPhoneNo(phno))
    {
        string accNo=searchUser(,phno)
        if(accNo==NULL)
            sendPrompt(sock,"\n\nThe LINKING IS SUCCESSFUL. WELCOME....");
        handleClient(accNo,sock);
    }
}


// --- MAIN ---


// ---------- UDP Broadcast Function ----------
void broadcastServerIP() {
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    int broadcast = 1;
    setsockopt(udp_socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));

    sockaddr_in broadcast_addr{};
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(BROADCAST_PORT);
    broadcast_addr.sin_addr.s_addr = inet_addr("255.255.255.255");

    string message = "SERVER:" + to_string(TCP_PORT);

    while (true) {
        sendto(udp_socket, message.c_str(), message.length(), 0,
               (sockaddr*)&broadcast_addr, sizeof(broadcast_addr));
        cout << "[Broadcasting] " << message << "\n";
        sleep(2);
    }
}

// ---------- Main Function ----------
int main() {
    // Start UDP broadcasting
    thread broadcaster(broadcastServerIP);
    broadcaster.detach();

    // Setup TCP server
    int server_fd, new_sock;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(TCP_PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    cout << " Server is running on port " << TCP_PORT << " and broadcasting..." << endl;

    // Accept multiple clients
    while (true) {
        new_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        thread(entrance, new_sock).detach();
    }

    return 0;
}


