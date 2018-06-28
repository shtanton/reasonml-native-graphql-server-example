open Graphql_lwt;

type role = User | Admin;

let role = Schema.(
	enum(
		~values=[
			enum_value(
				~value= User,
				"USER"
			),
			enum_value(
				~value=Admin,
				"ADMIN"
			)
		],
		"role"
	)
);

type user = {
	id: int,
	name: string,
	role: role,
	friends: list(user)
};

let user = Schema.(obj(
	~fields=(user => [
		field(
			~args=[],
			~typ=non_null(int),
			~resolve = ((), p) => p.id,
			"id"
		),
		field(
			~args=[],
			~typ=non_null(string),
			~resolve=((), p) => p.name,
			"name"
		),
		field(
			~args=[],
			~typ=non_null(role),
			~resolve=((), p) => p.role,
			"role"
		),
		field(
			~args=[],
			~typ=list(non_null(user)),
			~resolve=((), p) => Some(p.friends),
			"friends"
		)
	]),
	"user"
));
