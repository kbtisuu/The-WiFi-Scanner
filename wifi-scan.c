#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

int main(int argc, char **argv) {
    char *device = NULL;
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    int snapshot_length = 1024;
    int promiscuous = 1;
    int timeout = 1000;

    // Get the first available network device
    device = pcap_lookupdev(error_buffer);
    if (device == NULL) {
        fprintf(stderr, "Could not find network device: %s\n", error_buffer);
        exit(1);
    }

    // Open the network device for capture
    handle = pcap_open_live(device, snapshot_length, promiscuous, timeout, error_buffer);
    if (handle == NULL) {
        fprintf(stderr, "Could not open network device: %s\n", error_buffer);
        exit(1);
    }

    // Start capturing packets
    pcap_loop(handle, -1, process_packet, NULL);

    // Cleanup
    pcap_close(handle);

    return 0;
}

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    const struct ether_header *ethernet_header;
    const struct ieee80211_frame *wifi_header;
    const u_char *payload;
    int payload_size;
    char ssid[32];
    int channel;
    int rssi;
    
    // Check if this is a wireless packet
    ethernet_header = (struct ether_header*)packet;
    if (ntohs(ethernet_header->ether_type) != ETHERTYPE_IEEE80211) {
        return;
    }

    // Extract the wireless header
    wifi_header = (struct ieee80211_frame*)(packet + sizeof(struct ether_header));

    // Extract the payload
    payload = packet + sizeof(struct ether_header) + sizeof(struct ieee80211_frame);
    payload_size = header->len - sizeof(struct ether_header) - sizeof(struct ieee80211_frame);

    // Check if this is a beacon frame
    if (wifi_header->frame_control.type != IEEE80211_TYPE_MGMT ||
        wifi_header->frame_control.subtype != IEEE80211_STYPE_BEACON) {
        return;
    }

    // Extract the SSID
    memset(ssid, 0, sizeof(ssid));
    memcpy(ssid, payload + 36, payload[37]);

    // Extract the channel and RSSI
    channel = payload[14];
    rssi = (signed char)payload[22];

    // Print the information
    printf("SSID: %s\n", ssid);
    printf("Channel: %d\n", channel);
    printf("RSSI: %d dBm\n", rssi);
    printf("--------\n");
}
