open Lwt;
open Graphql_lwt;
open User;

let rec alice = {
	id: 1,
	name: "Alice",
	role: Admin,
	friends: [bob]
} and bob = {
	id: 2,
	name: "Bob",
	role: User,
	friends: [alice]
};

let users = [alice, bob];

let schema = Schema.(
	schema([
				 io_field(
					 ~args=[],
					 ~typ=non_null(list(non_null(user))),
					 ~resolve=((), ()) => Lwt.return(users),
					 "users"
				 ),
				 field(
					 ~args=Arg.([
											arg(
												~typ=non_null(obj(
														~coerce=(greeting, name) => (greeting, name),
														~fields=[
															arg'(~typ=string, ~default="hello", "greeting"),
															arg(~typ=non_null(string), "name")
														],
														"greeter_config"
												)),
												"config"
											)
					 ]),
					 ~typ=string,
					 ~resolve=((), (), (greeting, name)) => Some(Format.sprintf("%s, %s", greeting, name)),
					 "greeter"
				 )
	])
);
