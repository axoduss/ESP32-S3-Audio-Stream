#!/usr/bin/env python3
"""
WebSocket Bridge: UDP (ESP32) → WebSocket (Browser)
Compatibile con websockets >= 10.0
"""

import asyncio
import websockets
import socket
import logging

# Configurazione
UDP_IP = "0.0.0.0"
UDP_PORT = 9000
WS_PORT = 8765

# Store dei client WebSocket connessi
clients = set()

async def udp_listener():
    """Ascolta pacchetti UDP dall'ESP32 e li invia ai client WebSocket"""
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))
    sock.setblocking(False)
    
    print(f"📡 UDP listener attivo su {UDP_IP}:{UDP_PORT}")
    
    loop = asyncio.get_event_loop()
    
    while True:
        try:
            data, addr = await loop.sock_recvfrom(sock, 4096)
            if clients:
                # Invia a tutti i client connessi
                await asyncio.gather(
                    *[client.send(data) for client in clients],
                    return_exceptions=True
                )
        except Exception as e:
            await asyncio.sleep(0.01)

async def websocket_handler(websocket):
    """Gestisce connessioni WebSocket dai browser"""
    clients.add(websocket)
    print(f"✅ Client connesso. Totale clients: {len(clients)}")
    
    try:
        await websocket.wait_closed()
    finally:
        clients.remove(websocket)
        print(f"❌ Client disconnesso. Totale clients: {len(clients)}")

async def main():
    print(f"🌐 WebSocket server su ws://localhost:{WS_PORT}")
    print(f"🎧 Apri http://localhost:8080 nel browser\n")
    
    # Avvia server WebSocket
    async with websockets.serve(websocket_handler, "0.0.0.0", WS_PORT):
        # Avvia listener UDP
        await udp_listener()

if __name__ == "__main__":
    asyncio.run(main())