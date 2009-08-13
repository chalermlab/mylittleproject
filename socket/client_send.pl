#!/usr/bin/perl -w
use IO::Socket::INET;
# -----------------------------------------------------
#
# Send a command to the application!
#
# -----------------------------------------------------


sub send_command_data_n {

my ($args) = @_;


# Set to default if not defined 

$args->{marker}  = MARKER unless defined($args->{marker});

$args->{version} = PROTOCOL_VERSION unless defined($args->{version});
$args->{command}  = 0x12 unless defined($args->{command});
$args->{option}  = OPTION unless defined($args->{option});
$args->{result}  = RESULT unless defined($args->{result});
$args->{cmd_tag}  = int(rand(0xffffffff)) unless defined($args->{cmd_tag});
$args->{length}  = 0x0  unless defined($args->{length});
$args->{data}   = 0x0  unless defined($args->{data});
$args->{dw0}   = 0x0  unless defined($args->{dw0});
$args->{dw1}   = 0x0  unless defined($args->{dw1});
$args->{dw2}   = 0x0  unless defined($args->{dw2});
$args->{dw3}   = 0x0  unless defined($args->{dw3});


  $Cmd = { version => $args->{version}, cmd => $args->{command} ,option => $args->{option}, result => $args->{result}, cmd_tag=> 
           $args->{cmd_tag}, length=> $args->{length} 
         };

  print "subcmd: " . $args->{subcmd};
  $Cmd->{specific}->{hw_test}->{sub_cmd} = $args->{subcmd};
  print "dw0: " . $args->{dw0};
  $Cmd->{specific}->{hw_test}->{dw}[0] = $args->{dw0};
  $Cmd->{specific}->{hw_test}->{dw}[1] = $args->{dw1};
  $Cmd->{specific}->{hw_test}->{dw}[2] = $args->{dw2};
  $Cmd->{specific}->{hw_test}->{dw}[3] = $args->{dw3};


  $pack = $args->{packet}->pack('Cmd', $Cmd);

  $args->{socket}->send($args->{marker});
  $args->{socket}->send($pack);

# data

for ($i= 0; $i < $args->{length}; $i++) {
 $n = pack "c", $args->{data}; 
 $args->{socket}->send($n);
# $args->{data}++;
}

}

#-------------------------------------------------------------------------------
# Command()
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Description  : 
#                
# Input        : -
# Return       : 
#-------------------------------------------------------------------------------

sub recv_hwtest {

$s = shift;
$c = shift;

$$s->read($reply,1);     # read marker!


$Reply = $$c->sizeof('Cmd');

$$s->read($reply,$Reply);

$x1= $$c->unpack('Cmd', $reply);

#print Dumper($x1);


return;

 print "Cmd.version = $x1->{version}\n";
 print "Cmd.cmd = $x1->{cmd}\n";
 print "Cmd.option = $x1->{option}\n";
# print "Cmd.cmd_tag = $x1->{cmd_tag}\n";
 printf ("Cmd.cmd_tag =%lx\n", $x1->{cmd_tag});
 printf ("Cmd.length =%lx\n", $x1->{length});
 printf ("Cmd.result =%lx\n", $x1->{result});
# printf ("sub_cmd =%x\n", $x1->{specific}->{hw_test}->{sub_cmd});
 print "sub_cmd:$x1->{specific}->{hw_test}->{sub_cmd}\n";

 printf ("dw0 =%lx\n", $x1->{specific}->{hw_test}->{dw}[0]);
 printf ("dw1 =%lx\n", $x1->{specific}->{hw_test}->{dw}[1]);
 printf ("dw2 =%lx\n", $x1->{specific}->{hw_test}->{dw}[2]);
 printf ("dw3 =%lx\n", $x1->{specific}->{hw_test}->{dw}[3]);

}



# Main
 $sock = IO::Socket::INET->new(PeerAddr => '127.0.0.1',
			       PeerPort => '4390', 
                                 Proto    => 'tcp') or die "no socket"; 

#  print "Hej hopp \n";
  $sock->send("Hej hopp!\n\0");


__END__
