#!/usr/bin/env python

import sys, wave

#
# "Modem" wav creator for "Next Gen" Tagsu Modem :)
#
# Author: Jari Tulilahti
# Copyright: 2014 Rakettitiede Oy
# License: LGPLv3, see COPYING and COPYING.LESSER -files for more info
#
# Usage:
#	python modem.py <input_filename> [output_wav_filename] [samplerate]
#
# Default sample rate is 48000
# Default output to stdout if no wav filename given
#
# Working sample rates are between 16000 - 48000:
#
# 16000 (~4000 bps)
# 22050 (~5500 bps)
# 24000 (~6000 bps)
# 32000 (~8000 bps)
# 44100 (~11025 bps)
# 48000 (~12000 bps)
#
# NOTICE:
#
# Actual speed depends of the data, as zeroes and ones take
# different amount of samples, the more zeros, the faster the speed.
# Average bps has been calculated using data "0101010101..."
#

class modem:

	bits = [[3 * chr(0), 5 * chr(0)], [3 * chr(255), 5 * chr(255)]]
	sync = [17 * chr(0), 17 * chr(255)]
	hilo = 0

	# Nothing here
	def __init__(self):
		pass

	# Generate one sync-pulse
	def syncsignal(self):
		self.hilo ^= 1
		return self.sync[self.hilo]

	# Decode bits to modem signals
	def modemcode(self, byte):
		bleep = ""
		for x in xrange(8):
			self.hilo ^= 1
			bleep += self.bits[self.hilo][byte & 0x01]
			byte >>= 1
		return bleep

	# Return <length> samples of silence
	def silence(self, length):
		return chr(127) * length


if len(sys.argv) < 2:
	print """Usage: {0} <input_filename> [output_wav_filename] [samplerate]

	input_filename		Data file as input to modem.
	output_wav_filename	Write output-wav to this file. If empty, output to STDOUT.
	samplerate		Sample rate between 16000 - 48000. Default is 48000.
	""".format(sys.argv[0])
	sys.exit()

sound = ""

m = modem()
cnt = 0

# Add silence
# sound += m.silence(24000)

# Add 4 sync signals to start
for x in xrange(4):
	sound += m.syncsignal()

# Send Actual data
f = open(sys.argv[1])
for byte in f.read():
	sound += m.modemcode(ord(byte))

	# Add counter
	cnt += 1

	# After every 10 bytes, send 2 sync signals
	if cnt == 10:
		for x in xrange(2):
			sound += m.syncsignal()
		cnt = 0

# End transmission with few sync-signals
for x in xrange(4):
	sound += m.syncsignal()

# Output the generated sound (no wav headers)
if len(sys.argv) <= 2:
	print sound
else:
	freq = int(sys.argv[3]) if len(sys.argv) > 3 else 48000
	wav = wave.open(sys.argv[2], 'wb')
	wav.setparams((1, 1, freq, 0, "NONE", None))
	wav.writeframes(sound)
	wav.close()

