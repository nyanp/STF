use strict;
use warnings;
use File::Find;
use IO::File;

my $dir = "../";

sub print_file_name {
    if( /\.(h|hpp|cpp)$/ ){
        print "$_( $File::Find::name )\n";
        my $io = IO::File->new($_,'r') or die "$!";
        my @data = $io->getlines;
        $io->close;
        $io = IO::File->new($_,'w') or die "$!";
        $io->print("/**\r\n");
        $io->print(' * @file   ' .$_."\r\n");
        $io->print(' * @brief  '."\r\n");
        $io->print(" *\r\n");
        $io->print(' * @author Taiga Nomi'."\r\n");
        $io->print(' * @date   2011.02.16'."\r\n");
        $io->print(" */\r\n");
        $io->print(@data);
        $io->close;
    }
}

find( \&print_file_name, $dir);
