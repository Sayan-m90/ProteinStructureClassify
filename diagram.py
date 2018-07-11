import math
import matplotlib.pyplot as plt; plt.rcdefaults()
import numpy as np
import matplotlib.pyplot as plot_url
import sys

def barcode():
	zeroes = []
	zeroesinf = []
	oners = []
	onersinf = []
	twoers = []
	twoersinf = []
	x = []
	maxx = [-1,-1,-1]

	with open(sys.argv[1], 'r') as file:
		for line in file:
			l = line.split(" ")
			if(l[2][:-1]=='inf'):
				l[2] = -(10)
			l[0] = int(l[0])
			l[1] = int(l[1])
			l[2] = int(l[2])

			if(l[0]==0):
				if(l[2]<0):
					zeroesinf.append(l[2])
				elif(zeroes == [] or (zeroes[-1] != (l[2]-l[1]))):	#check if same value is entered
					zeroes.append(l[2]-l[1])
					if(l[2]-l[1]>maxx[0]):
						maxx[0] = l[2]-l[1]
			elif (l[0]==1):
				if(l[2]<0):
					onersinf.append(l[2])
				elif(oners == [] or (oners[-1] != (l[2]-l[1]))):
					oners.append(l[2]-l[1])
					if(l[2]-l[1]>maxx[1]):
						maxx[1] = l[2]-l[1]
			else:
				if(l[2]<0):
					twoersinf.append(l[2])
				elif(twoers == [] or (twoers[-1] != (l[2]-l[1]))):
					twoers.append(l[2]-l[1])
					if(l[2]-l[1]>maxx[2]):
						maxx[2] = l[2]-l[1]

	# print(twoers)
	for ind, val in enumerate(zeroesinf):
		zeroesinf[ind] = maxx[0]+20
	for ind, val in enumerate(onersinf):
		onersinf[ind] = maxx[1]+20
	for ind, val in enumerate(twoersinf):
		twoersinf[ind] = maxx[2]+20

	# print(zeroesinf)
	# print(zeroes)
	z = [len(zeroes),len(oners),len(twoers)]
	zeroes.extend(zeroesinf)
	oners.extend(onersinf)
	twoers.extend(twoersinf)
	zeroesinf = zeroes
	onersinf = oners
	twoersinf = twoers

	zeroesinf = list(reversed(zeroesinf))
	y_pos = np.arange(len(zeroesinf))

	fig = plt.figure(1)
	name = sys.argv[1].split("/")
	fig.canvas.set_window_title(name[-1])

	# print(sys.argv[1])
	# plt.suptitle(sys.argv[1])
	plt.subplot(311)
	plt.xlabel('0-dim')
	plt.xlim([0,maxx[0]+19])	
	barlist0=plt.barh(y_pos, zeroesinf, align='center', color='red', edgecolor = 'none')

	for ind in range(0,len(zeroesinf)-z[0]):
		barlist0[ind].set_color('black')

	onersinf = list(reversed(onersinf))
	y_pos = np.arange(len(onersinf))
	plt.subplot(312)
	plt.xlabel('1-dim')
	plt.xlim([0,maxx[1]+19])
	barlist1=plt.barh(y_pos, onersinf, align='center', color='cyan', edgecolor = 'none')
	for ind in range(0,len(onersinf)-z[1]):
		barlist1[ind].set_color('black')


	twoersinf = list(reversed(twoersinf))
	y_pos = np.arange(len(twoersinf))
	plt.subplot(313)
	plt.xlabel('2-dim')
	plt.xlim([0,maxx[2]+19])
	barlist2=plt.barh(y_pos, twoersinf, align='center', color='green', edgecolor = 'none')
	for ind in range(0,len(twoersinf)-z[2]):
		barlist2[ind].set_color('black')

	plt.show()



def pd():
	zeroesx = []
	zeroesy = []
	zeroesxi = []
	zeroesyi = []
	zeroesinf = []
	onersx = []
	onersy = []
	onersxi = []
	onersyi = []
	onersinf = []
	twoersx = []
	twoersy = []
	twoersxi = []
	twoersyi = []
	twoersinf = []

	maxx = [-1,-1,-1]
	maxy = [-1,-1,-1]

	with open(sys.argv[1], 'r') as file:
		for line in file:
			l = line.split(" ")
			if(l[2][:-1]=='inf'):
				l[2] = -10
			l[0] = int(l[0])
			l[1] = int(l[1])
			l[2] = int(l[2])
			# print((l[0]),(l[1]),l[2])

			if(l[0]==0):
				if(l[2]<0):
					zeroesinf.append(l[1])
				elif(zeroesx == [] or (zeroesx[-1] != l[1] or zeroesy[-1] != l[2])):	#check if same value is entered
					zeroesy.append(l[2])
					zeroesx.append(l[1])
				if(l[2]>maxy[0]):
					maxy[0] = l[2]
			elif (l[0]==1):
				if(l[2]<0):
					onersinf.append(l[1])
				elif(onersx == [] or (onersx[-1] != l[1] or onersy[-1] != l[2]  )):
					onersy.append(l[2])
					onersx.append(l[1])		

				if(l[2]>maxy[1]):
					maxy[1] = l[2]
			else:
				if(l[2]<0):
					twoersinf.append(l[1])
				elif(twoersx == [] or (twoersx[-1] != l[1] or twoersx[-1] != l[2] )):
					twoersy.append(l[2])
					twoersx.append(l[1])

				if(l[2]>maxy[2]):
					maxy[2] = l[2]

	if(zeroesinf !=[]):
		maxy[0] = maxy[0]+11
	if(onersinf != []):
		maxy[1] = maxy[1]+11
	if(twoersinf != []):
		maxy[2] = maxy[2]+11
	[zeroesxi.append(i) for i in zeroesinf]
	[zeroesyi.append(maxy[0]) for i in enumerate(zeroesinf)]
	[onersxi.append(i) for i in onersinf]
	[onersyi.append(maxy[1]) for i in enumerate(onersinf)]
	[twoersxi.append(i) for i in twoersinf]
	[twoersyi.append(maxy[2]) for i in enumerate(twoersinf)]


	fig = plt.figure(1)
	name = sys.argv[1].split("/")
	fig.canvas.set_window_title(name[-1])
	plt.subplot(221)
	plt.axis('equal')

	plt.text(0, 0, r'0,1,2-dim Persistence Dgm.'+'\n' +name[-1], fontsize=15, horizontalalignment = 'center',verticalalignment = 'center', color = 'blue')



	plt.subplot(222)
	plt.axis('equal')
	plt.xlabel('0-dim')
	plt.plot(zeroesx, zeroesy, 'co')
	plt.plot(zeroesxi, zeroesyi, 'bo')
	plt.plot(range(0,maxy[0]),range(0,maxy[0]),'r--')


	plt.subplot(223)
	plt.axis('equal')
	plt.xlabel('1-dim')
	plt.plot(onersx, onersy, 'go')
	plt.plot(onersxi, onersyi, 'bo')
	plt.plot(range(0,maxy[1]),range(0,maxy[1]),'r--')


	# print(onersinf, onersx, onersy, maxy)
	# print(twoersinf, range(0,len(onersinf)))
	plt.subplot(224)
	plt.axis('equal')# axis = 'equal')#, adjustable='box-forced')
	plt.xlabel('2-dim')
	plt.plot(twoersx, twoersy, 'yo')
	plt.plot(twoersxi, twoersyi, 'co')
	plt.plot(range(0,maxy[2]),range(0,maxy[2]),'r--')
	
	plt.show()


if len(sys.argv) == 1:
    print 'need filename'
    sys.exit(-1)
elif len(sys.argv) == 2:
	print('need to know if PD or Barcode Required(1 for PD, 2 for Barcode)')
	sys.exit(-1)
if(sys.argv[2]=='1'):
	pd()
elif(sys.argv[2]=='2'):
	barcode()
else: print('option not found')