# State machine

## Description

This is an example of a fully generic finite state machine.
In this architecture, you create a state machine and may add
to it as many states as you want.

Each state will have its own condition list with conditions
that transit to another state.
These conditions will be verified every time the state
machine is updated. If the condition is met the state will
trigger an action.
This action can change the state automatically or even send a
signal to trigger an external action.

As a showcase in this repo, we build this state machine to monitor a gate.
Instructions to use it and make the tests are written below.

## Based on

<https://www.mkelly.me/blog/phaser-finite-state-machine/>

## Dependencies

All the commands used in this document are supposed to be ran in a Linux enviroment.

### Programs

`make`
`gcc`
`gcovr`
`python`
`awk`
`entr`
`doxygen`
`graphviz`

### Libraries

`check.h`
`fff.h`

## Using

### Testing

To test the repo use:

```bash
make test
```

If there is any error it will be shown in the last line.

### Run

To start the program use:

```bash
make run
```

This will start an instance of the state machine manager.

#### Commands

The basic Commands are:

Get the id of all state machines:

```sh
get devices
```

Get information about the running state machines.

```sh
get info <id> [<id> [<id> ...]]
```

Change state of the machine to `<statename>`.

```sh
set <statename> <id> [<id> [<id> ...]]
```

State names are case sensitive.

#### Transition table

<table style="display:flex; flex-direction: column; width: 100%;">
<tbody style="display:flex; flex-direction: column; width: 100%;">
	<tr style="display: flex; width: 100%;">
		<th style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">State</th>
		<th style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">Transits to</th>
	</tr>
	<tr style="display: flex; width: 100%;">
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">Locked</td>
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;"> Closed</td>
	</tr>
	<tr style="display: flex; width: 100%;">
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">Closed</td>
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">
			Locked<br>
			ForcedOpening<br>
			Opening
		</td>
	</tr>
	<tr style="display: flex; width: 100%;">
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">ForcedOpening</td>
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">
			Open<br>
			Opening<br>
			InterruptedOpening
		</td>
	</tr>
	<tr style="display: flex; width: 100%;">
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">Opening</td>
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">
			Open<br>
			ForcedOpening<br>
			InterruptedOpening
		</td>
	</tr>
	<tr style="display: flex; width: 100%;">
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">InterruptedOpening</td>
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">
			InterruptedClosing<br>
			Opening<br>
			ForcedOpening
		</td>
	</tr>
	<tr style="display: flex; width: 100%;">
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">InterruptedClosing</td>
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">
			InterruptedOpening<br>
			Closing<br>
			ForcedClosing
		</td>
	</tr>
	<tr style="display: flex; width: 100%;">
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">Closing</td>
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">
			Closed<br>
			ForcedClosing<br>
			InterruptedClosing
		</td>
	</tr>
	<tr style="display: flex; width: 100%;">
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">ForcedClosing</td>
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">
			Closed<br>
			Closing<br>
			InterruptedClosing
		</td>
	</tr>
	<tr style="display: flex; width: 100%;">
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">Open</td>
		<td style="flex: 1; flex-grow: 1; width: 100%; text-align: center;">
			Closing<br>
			ForcedClosing
		</td>
	</tr>
</tbody>
</table>

### Configuration file

To generate the configuration file use:

```bash
make $(pwd)/.env
```

It will generate a file like this:

```yaml
Lock=22:00
Unlock=05:00
Open1=05:30
Open2=07:00
```

I recommend to change the values to a near time.
Some states will verify for auto transitions to these states.
The verification will continue for the time in the constants
found in the file `src/Instances_STM/Gate`.

Also in this file you may find the `SIGNAL_COOLDOWN` constant.
This constant is used to define a minimum time before sending another signal.

In a real situation, these signals would be sent to external devices that would
receive the signal, change its state and report a state change to our state machine.

In this test case, you should do it manually.

I.E.

```sh
set <statename> <ID>
```

### Documentation

To visualize the documentation use:

```bash
make serve
```

It will generate the documentation and coverage and
serve with python in the port `8000`.

<http://localhost:8000>

To only generate the docs use:

```bash
make doc
```

This alternative command will generate the documentation and
coverage in the `meta` directory.
Then you may use a web server of your choice to visualize the files:

```bash
python -m http.server --directory meta 8000
```

Or even:

```bash
live-server meta
```

### Watch

You may use `make watch` for a live development.
This command may be used in the root of the source or in a module.

```bash
make watch
```

By default this command will fire a  `make test` when the source is changed.
You may overwrite it using the `WCMD` variable.

```bash
make watch WCMD='run'
```

This command will fire a `make run` every time the source is changed.
In this case you won't be able to use the `stdin` of the program.

## Example

Run at 14:59:

`.env`

```yaml
Lock=15:00
Unlock=05:00
Open1=05:30
Open2=07:00
```

input/output:

```console
[ 22-12-2022 14:59:31 ]
The state machines were initalizated.
[ 22-12-2022 14:59:31 ]
Updating each 100ms
[ 22-12-2022 15:00:00 ]
1 - Sending signal:	Locked
2 - Sending signal:	Locked
set Locked 2
[ 22-12-2022 15:00:12 ]
2
ACTION: Gate locked.

[ 22-12-2022 15:00:21 ]
1 - Sending signal:	Locked
[ 22-12-2022 15:00:42 ]
1 - Sending signal:	Locked
set Closed 2
[ 22-12-2022 15:01:29 ]
2
ACTION: Gate closed.

set Opening 2
[ 22-12-2022 15:01:35 ]
2
ACTION: Opening gate.

set Open 2
[ 22-12-2022 15:01:42 ]
2
ACTION: Gate fully open.

[ 22-12-2022 15:02:13 ]
WARNNING: Time opened exceeded limit
[ 22-12-2022 15:02:24 ]
WARNNING: Time opened exceeded limit
[ 22-12-2022 15:02:35 ]
WARNNING: Time opened exceeded limit
set Closing 2
[ 22-12-2022 15:02:37 ]
2
ACTION: Gate started closing.

set InterruptedClosing 2
[ 22-12-2022 15:02:45 ]
2
WARNNING: Gate closing procces intrrupted!

set ForcedClosing 2
[ 22-12-2022 15:02:53 ]
2
WARNNING: Forced gate closing.

set Closed 2
[ 22-12-2022 15:03:00 ]
2
ACTION: Gate closed.
```

## Related docs

### Check

<https://libcheck.github.io/check/>

### fff

<https://github.com/meekrosoft/fff>

### Doxygen

<https://www.doxygen.nl/manual/index.html>

### Graphviz

<https://graphviz.org/>

### Entr

<https://github.com/eradman/entr>
