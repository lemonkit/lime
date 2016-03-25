name "github.com/lemonkit/lime"

plugin "github.com/gsmake/clang"

plugin "github.com/gsmake/lua"

task.copyexternal = function(self)
    local fs = require "lemoon.fs"
    local filepath = require "lemoon.filepath"

    local loader = self.Owner.Loader
    local buildconfig = self.Owner.Loader.Config.BuildConfig

    local sourcedir = filepath.toslash(filepath.join(
    self.Owner.Path,"external",
    loader.Config.TargetHost .. "-" .. loader.Config.TargetArch .. "-" .. buildconfig))

    local outputdir = filepath.toslash(filepath.join(
        loader.Temp,"clang",
        loader.Config.TargetHost .. "-" .. loader.Config.TargetArch .. "-" .. buildconfig))

    fs.copy_dir(sourcedir,outputdir,fs.update_existing)
end

task.resources = function(self)
end
task.resources.Prev = "copyexternal"

properties.lua = {
    dependencies        = {
        { name = "github.com/lemonkit/lemoon" };
    };
}


properties.clang = {
    ["lime"] = {
        type            = "static";
        dependencies    = {
            { name = "github.com/lemonkit/lemon" };

            "libEGL";

            "libGLESv2";
        };
    };

    ["lime-simulator"] = {
        path            = "simulator";
        type            = function(task)
            local host = task.Owner.Loader.Config.TargetHost

            if host == "Windows" then
                return "win32"
            else
                return "exe"
            end
        end;
        dependencies    = { "lime" };
    };
}
