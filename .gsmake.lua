name "github.com/lemonkit/lime"

version "develop"


plugin "github.com/gsmake/clang"

plugin "github.com/gsmake/lua"



lua = {
    dependencies    = {
        { name = "github.com/lemonkit/lemoon", version = "develop" };
    };
}


clang = {
    ["lime"] = {
        type            = "static";
        dependencies    = {
            { name = "github.com/lemonkit/lemon", version = "develop" };
        };
    }
}
