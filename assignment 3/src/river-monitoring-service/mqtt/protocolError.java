/**
 * Represents all the possible errors that a [Protocol] can raise.
 */
public interface ProtocolError {

    /**
     * Error raised when the [Protocol] tries to communicate with an [entity] that is not registered.
     */
    class EntityNotRegistered implements ProtocolError {
        private final Entity entity;

        public EntityNotRegistered(Entity entity) {
            this.entity = entity;
        }

        public Entity getEntity() {
            return entity;
        }
    }

    /**
     * Wrap the [exception] raised by the [Protocol] in a [ProtocolError].
     */
    class ProtocolException implements ProtocolError {
        private final Throwable exception;

        public ProtocolException(Throwable exception) {
            this.exception = exception;
        }

        public Throwable getException() {
            return exception;
        }
    }
}
