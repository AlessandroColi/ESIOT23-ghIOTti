package mqtt;
/**
 * Represents all the possible errors that a [Protocol] can raise.
 */
public abstract class ProtocolError extends Throwable {

    /**
     * Error raised when the [Protocol] tries to communicate with an [entity] that is not registered.
     */
    static class EntityNotRegistered extends ProtocolError {
        private final String entity;

        public EntityNotRegistered(String entity) {
            this.entity = entity;
        }

        public String getEntity() {
            return entity;
        }
    }

    /**
     * Wrap the [exception] raised by the [Protocol] in a [ProtocolError].
     */
    static class ProtocolException extends ProtocolError {
        private final Throwable exception;

        public ProtocolException(Throwable exception) {
            this.exception = exception;
        }

        public Throwable getException() {
            return exception;
        }
    }
}
