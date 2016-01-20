#!/usr/bin/perl -C31
#
# License: Just keep the following comment lines intact and
#          you can do whatever you want with this code
#
# Author: Stanislav Lechev [0xAF.org] <firedust@gmail.com>
#
# this tool is used in 400plus project to generate the languages.ini file.
# http://code.google.com/p/400plus
#
# If you need some new functionality in this script, please fill a new issue with request/patch:
# http://code.google.com/p/400plus/issues/entry

my $VERSION = "20120401.01";

use strict;
use Getopt::Long;
use Pod::Usage;

# perl+utf8 madness (-C31 should do the trick anyway)
use utf8;
use open qw( :std :encoding(utf8) );
binmode STDOUT, ":encoding(utf8)";
binmode STDIN, ":encoding(utf8)";

my @camera_languages = ( # excluding 'English', as it's hardcoded in the hack
	'German', 'French', 'Dutch', 'Danish', 'Finnish',
	'Italian', 'Norwegian', 'Swedish', 'Spanish',
	'Russian', 'Simplified_Chinese', 'Traditional_Chinese',
	'Korean', 'Japanese', 'Polish',
);
my %out_hash;
$out_hash{uc($_)} = () foreach (@camera_languages);

# options {{{
my $verbose = 0;
my $lang_files_dir = ".";
my $header_file = "../languages.h";
my $out_file = "../languages.ini";
my $gen_new_lang = 0;
my $check_lang_file = '';
my $quiet = 0;

Getopt::Long::Configure ("bundling");
GetOptions (
	'help|h'		=> sub { pod2usage(-exitstatus => 1, -verbose => 1); },
	'man'			=> sub { pod2usage(-exitstatus => 0, -verbose => 3); },
	"verbose+"		=> \$verbose,
	"v+"			=> \$verbose,
	"version|V"		=> sub { print "Version: $VERSION\n"; exit(0); },
	'lang-files-dir|f=s'   => \$lang_files_dir,
	'header|l=s'           => \$header_file,
#	'gen-new-lang|g=i'     => \$gen_new_lang,
	'gen-new-lang|g'       => \$gen_new_lang,
	'check-lang-file|c=s'  => \$check_lang_file,
	'output|o=s'           => \$out_file,
	'quiet|q'              => \$quiet,
) || pod2usage(1);
#}}}

info("lang_tool.pl - Language tool for 400plus project. http://code.google.com/p/400plus\n\n");

# parse header file {{{
my %lang_keys;
(-f $header_file && open (HF, $header_file)) || die "cannot open the header file [$header_file]\n";

verbose("Parsing header file [$header_file] for keys.\n");
while (<HF>) {
	chomp;
	my ($k, $v) = (/^\s*LANG_PAIR\s*\(\s*([^,\s]+)\s*,\s*"([^"]+)"\s*\)\s*\\/);
	next unless ($k and $v);
	debug(sprintf("%3d: %-22s: %s\n",scalar(keys %lang_keys), $k, $v));
	$lang_keys{$k} = $v;
}
close(HF);
info("Found [".(keys %lang_keys)."] keys in header file.\n");
#}}}

# generate new_lang.ini {{{
if ($gen_new_lang) {
#	if (-f "$lang_files_dir/new_lang.ini") {
#		open (NL, "$lang_files_dir/new_lang.ini") || die "cannot open [$lang_files_dir/new_lang.ini], though it exists ???\n";
#		my $fnd = 0;
#		while (<NL>) {
#			chomp;
#			next unless /^; Rev: r(\d+)$/;
#			$fnd=$1;
#			verbose("found new_lang.ini from r$fnd\n");
#			if ($fnd==$gen_new_lang) {
#				info("new_lang.ini already generated from r$gen_new_lang, to force regenerate - remove new_lang.ini\n");
#				close(NL);
#				exit(0);
#			} else {
#				info("new_lang.ini from r$fnd found - regenerating.\n");
#			}
#		}
#		close (NL);
#		info("Cannot find current new_lang.ini's revision.\n") if (!$fnd);
#	}
	info("Generating new_lang.ini...\n");
	open(NL, ">$lang_files_dir/new_lang.ini") || die "cannot open $lang_files_dir/new_lang.ini for writing.\n";
	print NL "; MYLANG language\n";
	print NL "; Translator: My Name <my\@email.com>\n";
	print NL "; Date: DD.MM.YYYY\n";
#	print NL "; Rev: r$gen_new_lang\n";
	print NL "[MYLANG]\n";
	foreach (sort(keys(%lang_keys))) {
		print NL sprintf("%-22s = %s\n", $_, $lang_keys{$_});
	}
	close (NL);
	exit(0);
}
#}}}

# check language file {{{
if ($check_lang_file) {
	info("\nChecking $lang_files_dir/$check_lang_file file.\n");
	(-d $lang_files_dir && -f "$lang_files_dir/$check_lang_file" && open(LF, "$lang_files_dir/$check_lang_file"))
		|| die "cannot open lang file [$lang_files_dir/$check_lang_file]\n";

	my %keys_found;
	my %keys_extra;
	my %keys_missing;

	while (<LF>) {
		chomp;
		next unless /^\s*(\w+)\s*=\s*(.*)\s*$/;
		$keys_found{$1} = $2;
		$keys_extra{$1} = $2 unless exists $lang_keys{$1};
	}
	close (LF);
	foreach (keys(%lang_keys)) {
		$keys_missing{$_} = $lang_keys{$_} unless exists $keys_found{$_};
	}

	info("Found [".(keys %keys_found)."] keys in $check_lang_file.\n");

	if ($verbose and (keys %keys_extra or keys %keys_missing)) {
		info("\nExtra keys: ".(keys %keys_extra)."\n");
		info(sprintf("\t%-22s = %s\n", $_, $keys_extra{$_})) foreach (keys %keys_extra);
		info("\nMissing keys: ".(keys %keys_missing)."\n");
		info(sprintf("\t%-22s = %s\n", $_, $keys_missing{$_})) foreach (keys %keys_missing);
	} else {
		info("Extra keys: ".(keys %keys_extra)."\n");
		info("Missing keys: ".(keys %keys_missing)."\n");
		info("\nRun with -v to see the missing/extra keys\n") unless ($verbose);
	}
	exit (0);
}
#}}}

# read languages {{{
(-d $lang_files_dir && opendir(my $dh, $lang_files_dir)) || die "cannot open dir [$lang_files_dir]\n";
verbose("searching for language files in [$lang_files_dir]\n");
my @lang_files = grep { /\.ini$/i && !/^languages\.ini$/ && !/^new_lang.ini$/ && -f "$lang_files_dir/$_" } readdir($dh);
closedir $dh;

die "no language files found in [$lang_files_dir]\n" if ($#lang_files < 0);

info("Found [".($#lang_files+1)."] language files.\n");
foreach my $lf(@lang_files) {
	debug("$lf\n");
	(-f "$lang_files_dir/$lf" && open(LF, "$lang_files_dir/$lf"))
		|| die "cannot open lang file [$lang_files_dir/$lf]\n";

	my ($l) = ($lf =~ /^(.*)\.ini$/i);
	while (<LF>) {
		chomp;
		next if $_ =~ /^;*\s*$/;
		$out_hash{uc($l)} .= "$_\n";
	}
	close(LF);
}
#}}}

open (OF, ">$out_file") || die "cannot open output file [$out_file] for writing\n";
print OF "; Languages for 400plus\n";
print OF ";\n";
print OF "; info for translators: http://code.google.com/p/400plus/wiki/TranslatorsGuide\n";
print OF ";\n";
print OF "; generated on: ".scalar(localtime())."\n";
print OF ";\n\n";

foreach(sort keys (%out_hash)) {
	if ($out_hash{$_} eq '') {
		print OF "[$_]\n; translator wanted\n\n";
	} else {
		print OF $out_hash{$_}."\n";
	}
}

close (OF);

exit (0);

# helper routines {{{
sub info { print shift unless $quiet; }
sub verbose { print "NOTICE: ".shift if $verbose; }
sub debug { print "DEBUG: ".shift if $verbose>1; }
#}}}



__END__

=head1 NAME

lang_tool.pl - Tool to verify language files and generate languages.ini for 400plus project.

=head1 SYNOPSIS

lang_tool.pl [options]

  Options:
    -h, --help                       - brief help (this)
    --man                            - full help
    -V, --version                    - show version
    -v, --verbose                    - enable verbose (use second time for debug)
    -f dir, --lang-files-dir dir     - search for language files in 'dir'
    -l file, --header file           - languages.h header file
    -g rev, --gen-new-lang rev       - generate new_lang.ini
    -c file, --check-lang-file file  - check language file for missing/extra keys
    -o file, --output file           - output file [default: ../languages.ini]

When called w/o options this tool will generate languages.ini from available languages.

=head1 OPTIONS

=over 4

=item B<--help>

Print a brief help message and exits.

=item B<--man>

Prints the full documentation in a manual page and exits.

=item B<--version>

Prints the version and exits.

=item B<--verbose>

Prints verbose information. Use -v second time to enable debug output.

=item B<--lang-files-dir> I<dir>

Search for separate language files (B<*.ini>) in this I<dir>.

Note: B<languages.ini> and B<new_lang.ini> files are skipped.

=item B<--header> I<file>

Read the language keys from header B<file> (languages.h)

=item B<--gen-new-lang>

Generate new_lang.ini file (with english language) and exit.
This file is a base template for new languages.

=item B<--check-lang-file> I<file>

Check language file I<file> for extra or missing keys.
Extra keys are to be removed, missing keys are to be added to file.

=item B<--output> I<file>

The output file B<languages.ini>.


=back

=head1 DESCRIPTION

B<lang_too.pl> will check the language files and generate the I<languages.ini> for B<400plus> project.
For more information about B<400plus>, check: http://code.google.com/p/400plus

=cut

# vim: ft=perl foldmethod=marker
