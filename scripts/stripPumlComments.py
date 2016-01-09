import os, re, sys

def parseArguments(args):
	if len(args) != 1:
		print >> sys.stderr, 'Expected exactly 1 argument, got %d' % len(args)
		sys.exit(-1)
	elif not os.path.isfile(args[0]):
		print >> sys.stderr, 'File "%s" does not exist' % args[0]
		sys.exit(-1)
	elif os.path.splitext(args[0])[1] != '.puml':
		print >> sys.stderr, 'File "%s" is not a .puml file' % args[0]
		sys.exit(-1)
	else:
		return args[0]
		
def main(args):
	pumlFilePath = parseArguments(args)

	lines = None
	with open(pumlFilePath, 'r') as pumlFile:
		lines = pumlFile.readlines()
	fileContent = ''.join(lines)
	fileContent = re.sub(r"/\'.*?\'/", '', fileContent, flags=re.DOTALL)
	fileContent = re.sub(r"\'.*?\n", '', fileContent, flags=re.DOTALL)

	print '\n'.join([l for l in [l.strip() for l in fileContent.split('\n')] if l != ''])


if __name__ == '__main__':
	main(sys.argv[1:])

