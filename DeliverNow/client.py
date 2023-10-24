 

__author__ = 'dadi'
#import socket for all socket related primitives
import socket
# we need struct in order to be able to pack data in
# a stream of bytes so that we can actually send
# an integer as a binary four byte sequence - instead
# of a string
import struct

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# input return actually a string and we need an int
a=int(input('a='))
b=int(input('b='))

# The obscure struct_addr is elegantly replaced by
# a simple pair - very convenient. Replace the IP Address with
# the one of your server
s.connect( ("10.152.1.189",1234) )
print("Connected")
# pack the value of a as a short int (16 bits) in network representation
res = s.send(struct.pack("!H", a))
print("Send")
res = s.send( struct.pack('!H', b))
print("Send")
c = s.recv(2)
print("Received")
# unpack the content read from the network into a short int
# and convert from network representation back to host
c = struct.unpack('!H',c)
print('a+b=' + c[0].__format__('d'))
    
s.close()

 